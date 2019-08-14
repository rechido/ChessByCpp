#include "GameState.h"
#include "Game.h"


GameState::GameState(Game* game, Board* board)
	: mGame(game)
	, mBoard(board)
{
	mScene.create(mBoard->getWidth(), mBoard->getHeight());

	if (!mFont.loadFromFile("arial.ttf"))
	{
		throw std::runtime_error("Unable to load the font file");
	}
	mText.setFont(mFont);
	mText.setCharacterSize(20);
	mText.setFillColor(Color::White);
	mText.setPosition(0, 0);
}


GameState::~GameState()
{
}
