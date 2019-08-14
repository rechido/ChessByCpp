#include "Ball.h"
#include <cassert>


Ball::Ball(eBallType type, float radius)
	: mType(type)
	, mVelocity(0.f, 0.f)
{
	setRadius(radius);
	FloatRect bounds = getLocalBounds();
	setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	//setOrigin(radius / 2, radius / 2);
	switch (type)
	{
	case eBallType::BALL_RED:
		setFillColor(Color::Red);
		break;
	case eBallType::BALL_BLACK:
		setFillColor(Color(100, 100, 100, 255));
		break;
	case eBallType::BALL_WHITE:
		setFillColor(Color::White);
		break;
	case eBallType::HOLE_BROWN:
		setFillColor(Color(102, 51, 0, 255));
		break;
	default:
		assert(false);
	}
}


Ball::~Ball()
{
}

Ball::eBallType Ball::getType() const
{
	return mType;
}

Vector2f Ball::getV() const
{
	return mVelocity;
}

void Ball::setV(Vector2f velocity)
{
	mVelocity = velocity;
}

