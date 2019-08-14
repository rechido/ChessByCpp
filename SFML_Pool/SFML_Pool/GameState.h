#pragma once
#include "Common.h"

#include "Board.h"

class Game;

class GameState
{
public:
	enum eGameState
	{
		START,
		PLAYING,
		WON,
		LOST,
		COUNT
	};

	GameState(Game* game, Board* board);
	virtual ~GameState();

	virtual void update() = 0;
	virtual void draw(RenderWindow& window) = 0;

	virtual void LeftKey() = 0;
	virtual void RightKey() = 0;
	virtual void UpKey() = 0;
	virtual void DownKey() = 0;
	virtual void EnterKey() = 0;
	virtual void EscapeKey() = 0;
	virtual void SpaceKey() = 0;

protected:
	Game* mGame;
	Board* mBoard;
	RenderTexture mScene;
	Font mFont;
	Text mText;

};

