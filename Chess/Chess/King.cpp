#include "King.h"

King::King(ePlayerType player, int position)
	: Piece(ePieceType::KING, player, position)
{
}

const char * King::GetRole()
{
	return " K ";
}

void King::CalculateMove(const unique_ptr<Piece> board[])
{
	mPossibleMove.clear();
	mPossibleMove.insert(mPosition);
	int x = mPosition % 8;
	int y = mPosition / 8;
	x++;
	if (x > 7)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	x--;
	if (x < 0)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	y++;
	if (y > 7)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	y--;
	if (y < 0)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	x++;
	y++;
	if (x > 7 || y > 7)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	x--;
	y--;
	if (x < 0 || y < 0)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	x++;
	y--;
	if (x > 7 || y < 0)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x = mPosition % 8;
	y = mPosition / 8;
	x--;
	y++;
	if (x < 0 || y > 7)
	{
	}
	else if (board[y * 8 + x] != nullptr)
	{
		if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	else
	{
		mPossibleMove.insert(y * 8 + x);
	}	
}