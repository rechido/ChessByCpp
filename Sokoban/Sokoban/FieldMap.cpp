#include "FieldMap.h"
#include "Object.h"

FieldMap::FieldMap()
{
	mPlayer = nullptr;
	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		int x = i % MAP_WIDTH;
		int y = i / MAP_WIDTH;
		if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
		{
			mObjectMap[i] = new Object(WALL); // 맵 가장자리는 벽으로 고정
		}
		else if (x == 1 && y == 1)
		{
			mObjectMap[i] = new Object(PLAYER);
			mPlayer = mObjectMap[i];
			mPlayerX = x;
			mPlayerY = y;
		}
		else
		{
			mObjectMap[i] = nullptr;
		}
	}
}

FieldMap::~FieldMap()
{
	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		Object* object = mObjectMap[i];
		if (object != nullptr)
		{
			delete object;
		}
	}
}

FieldMap* FieldMap::CopyAndReturnThisFieldMap()
{
	FieldMap* fieldMap = new FieldMap();

	fieldMap->PutObject(mPlayerX, mPlayerY, PLAYER);

	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		int x = i % MAP_WIDTH;
		int y = i / MAP_WIDTH;
		if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
		{
			continue; // 맵 가장자리는 벽으로 고정
		}
		else
		{
			Object* object = mObjectMap[i];
			if (object == nullptr)
			{
				continue;
			}
			else if (object->GetObjectType() == BOX)
			{
				fieldMap->PutObject(x, y, BOX);
			}
			else if (object->GetObjectType() == WALL)
			{
				fieldMap->PutObject(x, y, WALL);
			}
			else if (object->GetObjectType() == GOAL)
			{
				fieldMap->PutObject(x, y, GOAL);
			}
		}
	}
	return fieldMap;
}

void FieldMap::ResetFieldMapWithWalls()
{
	size_t width = GetMapWidth();
	size_t height = GetMapHeight();

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			PutObject(j, i, WALL);
		}
	}
}

void FieldMap::PutObject(int x, int y, eObjectType objectType)
{
	if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
	{
		assert(false); // 맵 밖에 물체를 놓을 수 없다.
	}
	if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
	{
		return; // 맵 가장자리는 벽으로 고정
	}

	if (mObjectMap[y*MAP_WIDTH + x] != nullptr)
	{
		if (objectType == mObjectMap[y*MAP_WIDTH + x]->GetObjectType())
		{
			return; // 물체를 놓으려는 곳에 이미 같은 타입의 물체가 있을 시 아무것도 실행하지 않음.
		}
		else if (mObjectMap[y*MAP_WIDTH + x]->GetObjectType() == PLAYER)
		{
			return; // 플레이어는 삭제 불가능. 플레이어를 다른 위치에 놓을 시 자동으로 이전 플레이어가 삭제.
		}
		else
		{
			delete mObjectMap[y*MAP_WIDTH + x];
			mObjectMap[y*MAP_WIDTH + x] = nullptr;
		}
	}

	if (objectType == WAY)
	{
		return;
	}
	else if (objectType == PLAYER)
	{
		// 플레이어는 반드시 하나 존재한다고 가정. 또한 플레이어는 반드시 하나만 존재해야함.
		mObjectMap[y*MAP_WIDTH + x] = mPlayer;
		mObjectMap[mPlayerY*MAP_WIDTH + mPlayerX] = nullptr;
		mPlayerX = x;
		mPlayerY = y;
	}
	else
	{
		mObjectMap[y*MAP_WIDTH + x] = new Object(objectType);
	}
}

void FieldMap::MovePlayerLeft()
{
	if (Push(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX - 1, mPlayerY);
		mPlayerX--;
	}
}

void FieldMap::MovePlayerRight()
{
	if (Push(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX + 1, mPlayerY);
		mPlayerX++;
	}
}

void FieldMap::MovePlayerUp()
{
	if (Push(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX, mPlayerY - 1);
		mPlayerY--;
	}
}

void FieldMap::MovePlayerDown()
{
	if (Push(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX, mPlayerY + 1);
		mPlayerY++;
	}
}

size_t FieldMap::GetMapWidth()
{
	return MAP_WIDTH;
}

size_t FieldMap::GetMapHeight()
{
	return MAP_HEIGHT;
}

Object* FieldMap::GetObject(int x, int y)
{
	return mObjectMap[y*MAP_WIDTH + x];
}

bool FieldMap::Push(int xFrom, int yFrom, int xTo, int yTo)
{
	// 대상 오브젝트를 미는데 성공했거나, 혹은 밀 대상이 없을 경우 참을 반환한다.

	if (xFrom < 0 || xFrom > MAP_WIDTH - 1 || yFrom < 0 || yFrom > MAP_HEIGHT - 1)
	{
		assert(false); // 밀어야 할 대상이 맵 밖에 존재하는 것은 불가능.
	}
	if (xTo < 0 || xTo > MAP_WIDTH - 1 || yTo < 0 || yTo > MAP_HEIGHT - 1)
	{
		return false;
	}

	Object* object = mObjectMap[yFrom*MAP_WIDTH + xFrom];
	Object* obstacle = mObjectMap[yTo*MAP_WIDTH + xTo];

	if (object != nullptr && object->GetObjectType() == PLAYER)
	{
		assert(false); // 그 어떤 경우에도 플레이어를 밀 수는 없다.
	}
	if (object == nullptr)
	{
		return true; // 밀려는 곳에 아무것도 없을시 아무 행동도 하지 않고 참을 반환.
	}
	else
	{
		if (object->GetObjectType() == BOX)
		{
			if (obstacle == nullptr || obstacle->GetObjectType() == GOAL)
			{
				StandOnTheWayOrGoal(xFrom, yFrom, xTo, yTo);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (object->GetObjectType() == WALL)
		{
			return false;
		}
		else if (object->GetObjectType() == GOAL)
		{
			if (!object->hasNext())
			{
				return true;
			}
			else
			{
				if (obstacle == nullptr || obstacle->GetObjectType() == GOAL)
				{
					StandOnTheWayOrGoal(xFrom, yFrom, xTo, yTo);
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
}

void FieldMap::StandOnTheWayOrGoal(int xFrom, int yFrom, int xTo, int yTo)
{
	// 이 명령은 실패하는 경우가 없다.
	Object* object = mObjectMap[yFrom*MAP_WIDTH + xFrom];
	Object* obstacle = mObjectMap[yTo*MAP_WIDTH + xTo];

	assert(object != nullptr); // 움직이려는 오브젝트는 널일 수 없다.
	assert(!(object->GetObjectType() == GOAL && !object->hasNext())); // 움직이려는 위치에 골이 있을 경우, 반드시 위에 오브젝트가 놓여있어야 한다.
	assert(obstacle == nullptr || obstacle->GetObjectType() == GOAL); // 도착 지점에는 널 아니면 골만이 있어야 한다.

	if (object->GetObjectType() == GOAL)
	{
		Object* goal = object;
		object = goal->GetNextObject();
		goal->SetNextObject(nullptr);
	}
	else
	{
		mObjectMap[yFrom*MAP_WIDTH + xFrom] = nullptr;
	}

	if (obstacle == nullptr)
	{
		mObjectMap[yTo*MAP_WIDTH + xTo] = object;
	}
	else if (obstacle->GetObjectType() == GOAL)
	{
		obstacle->SetNextObject(object);
	}

}
