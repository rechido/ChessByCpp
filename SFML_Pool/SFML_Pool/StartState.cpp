#include "StartState.h"
#include "Game.h"


StartState::StartState(Game* game, Board* board)
	: GameState(game, board)
{
	mText.setString("Press Enter to Start");
	FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	mText.setPosition(mBoard->getWidth() / 2, mBoard->getHeight() / 2);
}


StartState::~StartState()
{
}

void StartState::update()
{
}

void StartState::draw(RenderWindow& window)
{
	window.draw(mText);
}

void StartState::LeftKey()
{
}

void StartState::RightKey()
{
}

void StartState::UpKey()
{
}

void StartState::DownKey()
{
}

void StartState::EnterKey()
{
	mGame->changeGameState(PLAYING);
}

void StartState::EscapeKey()
{
}

void StartState::SpaceKey()
{
}
