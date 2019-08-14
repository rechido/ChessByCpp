#pragma once
#include "GameState.h"

class PlayingState :
	public GameState
{
public:
	PlayingState(Game* game, Board* board);
	~PlayingState();

	// GameState을(를) 통해 상속됨
	virtual void update() override;
	virtual void draw(RenderWindow & window) override;

	virtual void LeftKey() override;
	virtual void RightKey() override;
	virtual void UpKey() override;
	virtual void DownKey() override;
	virtual void EnterKey() override;
	virtual void EscapeKey() override;
	virtual void SpaceKey() override;

private:
	Text mShotSpeedText;
	Text mShotDegreeText;
	VertexArray mLine;
};

