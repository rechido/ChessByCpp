#pragma once
#include "Common.h"

#include "Ball.h"


class Board : public Drawable
{
public:
	enum eState
	{
		NOTHING,
		WHITEBALL_DEATH,
		BLACKBALL_DEATH_AT_LAST,
		BLACKBALL_DEATH_AT_FIRST,
		COUNT
	};

	Board(int width, int height);
	~Board();

	int getWidth() const;
	int getHeight() const;

	eState update();

	// Drawable을(를) 통해 상속됨
	virtual void draw(RenderTarget& target, RenderStates states) const override;

	Vector2f rotate(float degree, const Vector2f vector);

	void shot();
	void increaseSpeed();
	void decreaseSpeed();
	void clockwiseTurn();
	void counterClockwiseTurn();

	float getShotSpeed() const;
	float getShotDegree() const;
	float getWhiteBallSpeedNow();
	Vector2f getWhiteBallPosition() const;
	bool isEveryBallStopped();

private:
	inline float dot(const Vector2f& lv, const Vector2f& rv)
	{
		return lv.x * rv.x + lv.y * rv.y;
	}

	inline float length(const Vector2f& source)
	{
		return std::sqrt(dot(source, source));
	}

	void setInitialPosition();

	void updateVelocity();

	vector<Ball*> mBalls;
	float mCommonRadius;
	float mFrictionalVelocityDrop;

	vector<Ball*> mHoles;



	int mWidth;
	int mHeight;

	Font mFont;

	float mShotSpeed;
	float mShotDegree;
};

