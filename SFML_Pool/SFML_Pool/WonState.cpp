#include "WonState.h"



WonState::WonState(Game* game, Board* board)
	: GameState(game, board)
{
	mText.setString("Yon Won!");
	FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	mText.setPosition(mBoard->getWidth() / 2, mBoard->getHeight() / 2);
}


WonState::~WonState()
{
}

void WonState::update()
{
}

void WonState::draw(RenderWindow & window)
{
	window.draw(mText);
}

void WonState::LeftKey()
{
}

void WonState::RightKey()
{
}

void WonState::UpKey()
{
}

void WonState::DownKey()
{
}

void WonState::EnterKey()
{
}

void WonState::EscapeKey()
{
}

void WonState::SpaceKey()
{
}
