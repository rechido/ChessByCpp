#pragma once
#include "Common.h"


class Ball : public CircleShape
{
public:
	enum eBallType
	{
		BALL_RED,
		BALL_BLACK,
		BALL_WHITE,
		HOLE_BROWN,
		COUNT
	};

	Ball(eBallType type, float radius);
	~Ball();

	eBallType getType() const;

	Vector2f getV() const;
	void setV(Vector2f velocity);


private:
	eBallType mType;
	Vector2f mVelocity;


};

