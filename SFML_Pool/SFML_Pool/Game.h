#pragma once
#include "Common.h"
#include "GameState.h"
#include "Board.h"


class Game
{
public:
	Game();
	~Game();

	void run();
	void changeGameState(GameState::eGameState gameState);

private:
	Board mBoard;
	array<GameState*, GameState::COUNT> mGameStates;
	GameState::eGameState mCurrentState;
	RenderWindow mWindow;
	float mUpdateDuration;
};

