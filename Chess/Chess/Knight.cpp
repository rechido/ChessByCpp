#include "Knight.h"

Knight::Knight(ePlayerType player, int position)
	: Piece(ePieceType::KNIGHT, player, position)
{
}

const char * Knight::GetRole()
{
	return " N ";
}

void Knight::CalculateMove(const unique_ptr<Piece> board[])
{
	mPossibleMove.clear();
	mPossibleMove.insert(mPosition);
	int x = mPosition % 8;
	int y = mPosition / 8;
	x += 2;
	y += 1;
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
	x += 2;
	y -= 1;
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
	x -= 2;
	y -= 1;
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
	x -= 2;
	y += 1;
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
	x = mPosition % 8;
	y = mPosition / 8;
	x += 1;
	y += 2;
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
	x -= 1;
	y += 2;
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
	x = mPosition % 8;
	y = mPosition / 8;
	x += 1;
	y -= 2;
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
	x -= 1;
	y -= 2;
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
}
