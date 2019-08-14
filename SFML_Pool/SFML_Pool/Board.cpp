#include "Board.h"
#include <cassert>

Board::Board(int width, int height)
	: mCommonRadius(20.f)
	, mFrictionalVelocityDrop(0.1f)
	, mWidth(width)
	, mHeight(height)
	, mShotSpeed(0.f)
	, mShotDegree(0.f)
{
	if (!mFont.loadFromFile("arial.ttf"))
	{
		throw std::runtime_error("Unable to load the font file");
	}

	mBalls.reserve(16);
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			Ball* ball = new Ball(Ball::BALL_WHITE, mCommonRadius);
			mBalls.push_back(ball);
		}
		else if (i == 8)
		{
			Ball* ball = new Ball(Ball::BALL_BLACK, mCommonRadius);
			mBalls.push_back(ball);
		}
		else
		{
			Ball* ball = new Ball(Ball::BALL_RED, mCommonRadius);
			mBalls.push_back(ball);
		}
	}
	mHoles.reserve(6);
	for (int i = 0; i < 6; i++)
	{
		Ball* hole = new Ball(Ball::HOLE_BROWN, mCommonRadius * 1.5);
		mHoles.push_back(hole);
	}
	setInitialPosition();
}


Board::~Board()
{
}

int Board::getWidth() const
{
	return mWidth;
}

int Board::getHeight() const
{
	return mHeight;
}

Board::eState Board::update()
{
	updateVelocity();
	for (Ball* ball : mBalls)
	{

		Vector2f PosNow = ball->getPosition();
		Vector2f PosNew = ball->getPosition() + ball->getV();
		ball->setPosition(PosNew);
	}

	int ballCount = mBalls.size();
	// collision between a ball and a hole
	for (int i = 0; i < ballCount - 1; i++)
	{
		bool isErased = false;
		Ball* ball = mBalls[i];
		for (Ball* hole : mHoles)
		{
			Vector2f distance = ball->getPosition() - hole->getPosition();
			if (length(distance) < hole->getRadius() - ball->getRadius())
			{
				if (ball->getType() == Ball::BALL_WHITE)
				{
					return WHITEBALL_DEATH;
				}
				else if (ball->getType() == Ball::BALL_BLACK && mBalls.size() == 1 && mBalls[0]->getType() == Ball::BALL_WHITE)
				{
					return BLACKBALL_DEATH_AT_LAST;
				}
				else if (ball->getType() == Ball::BALL_BLACK)
				{
					return BLACKBALL_DEATH_AT_FIRST;
				}
				// if the ball is inside any holes, remove that ball
				mBalls.erase(mBalls.begin() + i);
				delete ball;
				isErased = true;

				break;
			}
		}
		if (isErased)
		{
			break;
		}
	}

	return NOTHING;
}

void Board::updateVelocity()
{
	int ballCount = mBalls.size();
	// collision between two balls
	for (int i = 0; i < ballCount - 1; i++)
	{
		for (int j = i + 1; j < ballCount; j++)
		{

			Vector2f distance = mBalls[i]->getPosition() - mBalls[j]->getPosition();
			if (length(distance) < mBalls[i]->getRadius() + mBalls[j]->getRadius())
			{
				float collisionAngle = atan2f(distance.y, distance.x) * 180.f / M_PI;
				Vector2f vPrevOrigini = mBalls[i]->getV();
				Vector2f vPrevCollisionCoordinatei = rotate(-collisionAngle, vPrevOrigini);
				Vector2f vPrevOriginj = mBalls[j]->getV();
				Vector2f vPrevCollisionCoordinatej = rotate(-collisionAngle, vPrevOriginj);
				Vector2f vNewCollisionCoordinatei(vPrevCollisionCoordinatej.x, vPrevCollisionCoordinatei.y);
				Vector2f vNewCollisionCoordinatej(vPrevCollisionCoordinatei.x, vPrevCollisionCoordinatej.y);
				Vector2f vNewOrigini = rotate(collisionAngle, vNewCollisionCoordinatei);
				Vector2f vNewOriginj = rotate(collisionAngle, vNewCollisionCoordinatej);
				Vector2f newDistance = (mBalls[i]->getPosition() + vNewOrigini) - (mBalls[j]->getPosition() + vNewOriginj);
				if (length(newDistance) - length(distance) > 0)
				{
					mBalls[i]->setV(vNewOrigini);
					mBalls[j]->setV(vNewOriginj);
				}
			}
		}
	}

	// collision between a ball and a wall
	for (Ball* ball : mBalls)
	{
		Vector2f position = ball->getPosition();
		float radius = ball->getRadius();
		if (position.x - radius <= 0 || position.x + radius >= mWidth)
		{
			Vector2f vPrev = ball->getV();
			ball->setV(Vector2f(-vPrev.x, vPrev.y));
		}
		if (position.y - radius <= 0 || position.y + radius >= mHeight)
		{
			Vector2f vPrev = ball->getV();
			ball->setV(Vector2f(vPrev.x, -vPrev.y));
		}
	}



	// add frictional force
	for (Ball* ball : mBalls)
	{
		Vector2f vPrev = ball->getV();
		float speedPrev = length(vPrev);
		if (speedPrev == 0.f)
		{
			continue;
		}
		float speedNew = speedPrev - mFrictionalVelocityDrop;
		if (speedNew < 0.f)
		{
			speedNew = 0.f;
		}
		Vector2f vNew = Vector2f(vPrev.x * speedNew / speedPrev, vPrev.y * speedNew / speedPrev);
		ball->setV(vNew);
	}
}

void Board::draw(RenderTarget& target, RenderStates states) const
{
	for (Ball* ball : mBalls)
	{
		target.draw(*ball, states);
	}
	for (Ball* hole : mHoles)
	{
		target.draw(*hole, states);
	}
}

void Board::setInitialPosition()
{
	int col = 0, row = 0;
	float xInit = mWidth / 8 * 6;
	float yInit = mHeight / 2;
	float xDis = mCommonRadius * sqrt(3);
	for (Ball* ball : mBalls)
	{
		if (ball->getType() == Ball::BALL_WHITE)
		{
			ball->setPosition(mWidth / 8, mHeight / 2);
		}
		else
		{
			if (row > col)
			{
				col++;
				row = 0;
			}
			Vector2f position(xInit + xDis * col, yInit - mCommonRadius * col + mCommonRadius * row * 2);
			ball->setPosition(position);
			row++;
		}
	}

	mHoles[0]->setPosition(mHoles[0]->getRadius(), mHoles[0]->getRadius());
	mHoles[1]->setPosition(mWidth / 2 + mHoles[1]->getRadius(), mHoles[1]->getRadius());
	mHoles[2]->setPosition(mWidth - mHoles[2]->getRadius(), mHoles[2]->getRadius());
	mHoles[3]->setPosition(mHoles[3]->getRadius(), mHeight - mHoles[3]->getRadius());
	mHoles[4]->setPosition(mWidth / 2 + mHoles[4]->getRadius(), mHeight - mHoles[4]->getRadius());
	mHoles[5]->setPosition(mWidth - mHoles[5]->getRadius(), mHeight - mHoles[5]->getRadius());
}

Vector2f Board::rotate(float degree, const Vector2f vector)
{
	float rad = degree * M_PI / 180.f;
	float xNew = vector.x * cos(rad) - vector.y * sin(rad);
	float yNew = vector.x * sin(rad) + vector.y * cos(rad);
	return Vector2f(xNew, yNew);
}

void Board::shot()
{
	Vector2f velocity(mShotSpeed * cos(mShotDegree * M_PI / 180.f), mShotSpeed * sin(mShotDegree * M_PI / 180.f));
	mBalls[0]->setV(velocity);
}

void Board::increaseSpeed()
{
	if (mShotSpeed < 50.f)
	{
		mShotSpeed = mShotSpeed + 5.f;
	}
}

void Board::decreaseSpeed()
{
	if (mShotSpeed > 0.f)
	{
		mShotSpeed = mShotSpeed - 5.f;
	}
}

void Board::clockwiseTurn()
{
	mShotDegree = mShotDegree + 1.f;
	if (mShotDegree == 360)
	{
		mShotDegree = 0;
	}
}

void Board::counterClockwiseTurn()
{

	if (mShotDegree == 0)
	{
		mShotDegree = 360;
	}
	mShotDegree = mShotDegree - 1.f;
}

float Board::getShotSpeed() const
{
	return mShotSpeed;
}

float Board::getShotDegree() const
{
	return mShotDegree;
}

float Board::getWhiteBallSpeedNow()
{
	return length(mBalls[0]->getV());
}

Vector2f Board::getWhiteBallPosition() const
{
	return mBalls[0]->getPosition();
}

bool Board::isEveryBallStopped()
{
	for (Ball* ball : mBalls)
	{
		if (length(ball->getV()) > 0.f)
		{
			return false;
		}
	}
	return true;
}
