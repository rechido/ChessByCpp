#include "LostState.h"



LostState::LostState(Game* game, Board* board)
	: GameState(game, board)
{
	mText.setString("You Lost!");
	FloatRect textRect = mText.getLocalBounds();
	mText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	mText.setPosition(mBoard->getWidth() / 2, mBoard->getHeight() / 2);
}


LostState::~LostState()
{
}

void LostState::update()
{
}

void LostState::draw(RenderWindow & window)
{
	window.draw(mText);
}

void LostState::LeftKey()
{
}

void LostState::RightKey()
{
}

void LostState::UpKey()
{
}

void LostState::DownKey()
{
}

void LostState::EnterKey()
{
}

void LostState::EscapeKey()
{
}

void LostState::SpaceKey()
{
}
