#include "Object.h"

Object::Object(eObjectType objectType)
	: mObjectType(objectType)
{
	mNext = nullptr;
}

Object::~Object()
{
}

bool Object::hasNext()
{
	if (mNext != nullptr)
	{
		return true;
	}
	return false;
}

void Object::SetObjectType(eObjectType objectType)
{
	mObjectType = objectType;
}

eObjectType Object::GetObjectType()
{
	return mObjectType;
}

void Object::SetNextObject(Object * nextObject)
{
	mNext = nextObject;
}

Object* Object::GetNextObject()
{
	return mNext;
}
