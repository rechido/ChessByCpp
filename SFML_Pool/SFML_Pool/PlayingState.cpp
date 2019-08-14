#include "PlayingState.h"
#include "Game.h"


PlayingState::PlayingState(Game* game, Board* board)
	: GameState(game, board)
	, mLine(LinesStrip, 2)
{
	mShotSpeedText.setFont(mFont);
	mShotSpeedText.setCharacterSize(20);
	mShotSpeedText.setFillColor(Color::White);
	mShotSpeedText.setPosition(0, mBoard->getHeight());

	mShotDegreeText.setFont(mFont);
	mShotDegreeText.setCharacterSize(20);
	mShotDegreeText.setFillColor(Color::White);
	mShotDegreeText.setPosition(200, mBoard->getHeight());

	mLine[0].position = Vector2f(mBoard->getWidth() / 8, mBoard->getHeight() / 2);
	mLine[0].color = Color::Blue;
	mLine[1].position = Vector2f(mBoard->getWidth(), mBoard->getHeight() / 2);
	mLine[1].color = Color::Blue;
}


PlayingState::~PlayingState()
{
}

void PlayingState::update()
{
	Board::eState state = mBoard->update();
	switch (state)
	{
	case Board::WHITEBALL_DEATH:
		mGame->changeGameState(GameState::LOST);
		break;
	case Board::BLACKBALL_DEATH_AT_FIRST:
		mGame->changeGameState(GameState::LOST);
		break;
	case Board::BLACKBALL_DEATH_AT_LAST:
		mGame->changeGameState(GameState::WON);
		break;
	case Board::NOTHING:
		break;
	default:
		assert(false);
	}
	mShotSpeedText.setString("Speed: " + to_string(mBoard->getShotSpeed()));
	mShotDegreeText.setString("Angle: " + to_string(mBoard->getShotDegree()));
	Vector2f whiteBallPosition = mBoard->getWhiteBallPosition();
	mLine[0].position = whiteBallPosition;
	Vector2f endOfLine = Vector2f(whiteBallPosition.x + mBoard->getWidth() * cos(mBoard->getShotDegree() * M_PI / 180), whiteBallPosition.y + mBoard->getWidth() * sin(mBoard->getShotDegree() * M_PI / 180));
	mLine[1].position = endOfLine;
}

void PlayingState::draw(RenderWindow& window)
{
	window.draw(*mBoard);
	window.draw(mShotSpeedText);
	window.draw(mShotDegreeText);
	if (mBoard->isEveryBallStopped())
	{
		window.draw(mLine);
	}

}

void PlayingState::LeftKey()
{
	if (mBoard->isEveryBallStopped())
	{
		mBoard->counterClockwiseTurn();
	}
}

void PlayingState::RightKey()
{
	if (mBoard->isEveryBallStopped())
	{
		mBoard->clockwiseTurn();
	}
}

void PlayingState::UpKey()
{
	if (mBoard->isEveryBallStopped())
	{
		mBoard->increaseSpeed();
	}
}

void PlayingState::DownKey()
{
	if (mBoard->isEveryBallStopped())
	{
		mBoard->decreaseSpeed();
	}
}

void PlayingState::EnterKey()
{
	if (mBoard->isEveryBallStopped())
	{
		mBoard->shot();
	}
}

void PlayingState::EscapeKey()
{
}

void PlayingState::SpaceKey()
{
}
