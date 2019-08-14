#include "Game.h"
#include "StartState.h"
#include "PlayingState.h"
#include "WonState.h"
#include "LostState.h"



Game::Game()
	: mBoard(1280, 720)
	, mCurrentState(GameState::START)
	, mWindow(VideoMode(mBoard.getWidth(), mBoard.getHeight() + 50), "Pool")
	, mUpdateDuration(1.f / 60.f) // update rate is 60hz

{
	mGameStates[GameState::START] = new StartState(this, &mBoard);
	mGameStates[GameState::PLAYING] = new PlayingState(this, &mBoard);
	mGameStates[GameState::WON] = new WonState(this, &mBoard);
	mGameStates[GameState::LOST] = new LostState(this, &mBoard);
}


Game::~Game()
{
}

void Game::run()
{
	Clock frameClock;
	while (mWindow.isOpen())
	{
		if (frameClock.getElapsedTime().asSeconds() < mUpdateDuration)
		{
			continue;
		}
		Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				mWindow.close();
			}
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Left:
					mGameStates[mCurrentState]->LeftKey();
					break;
				case Keyboard::Right:
					mGameStates[mCurrentState]->RightKey();
					break;
				case Keyboard::Up:
					mGameStates[mCurrentState]->UpKey();
					break;
				case Keyboard::Down:
					mGameStates[mCurrentState]->DownKey();
					break;
				case Keyboard::Enter:
					mGameStates[mCurrentState]->EnterKey();
					break;
				case Keyboard::Escape:
					mGameStates[mCurrentState]->EscapeKey();
					break;
				case Keyboard::Space:
					mGameStates[mCurrentState]->SpaceKey();
					break;
				}
			}
		}

		mGameStates[mCurrentState]->update();
		frameClock.restart();
		mWindow.clear();
		mGameStates[mCurrentState]->draw(mWindow);
		mWindow.display();
	}
}

void Game::changeGameState(GameState::eGameState gameState)
{
	mCurrentState = gameState;
}
