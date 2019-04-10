#include "Rook.h"

Rook::Rook(ePlayerType player, int position)
	: Piece(ePieceType::ROOK, player, position)
{
}

void Rook::CalculateMove(const unique_ptr<Piece> board[])
{
	mPossibleMove.clear();
	mPossibleMove.insert(mPosition);
	int x = mPosition % 8;
	int y = mPosition / 8;
	while (true)
	{
		x++;
		if (x > 7)
		{
			break;
		}
		else if (board[y * 8 + x] != nullptr)
		{
			if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
			{
				mPossibleMove.insert(y * 8 + x);
			}
			break;
		}
		else
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	x = mPosition % 8;
	y = mPosition / 8;
	while (true)
	{
		x--;
		if (x < 0)
		{
			break;
		}
		else if (board[y * 8 + x] != nullptr)
		{
			if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
			{
				mPossibleMove.insert(y * 8 + x);
			}
			break;
		}
		else
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	x = mPosition % 8;
	y = mPosition / 8;
	while (true)
	{
		y++;
		if (y > 7)
		{
			break;
		}
		else if (board[y * 8 + x] != nullptr)
		{
			if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
			{
				mPossibleMove.insert(y * 8 + x);
			}
			break;
		}
		else
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
	x = mPosition % 8;
	y = mPosition / 8;
	while (true)
	{
		y--;
		if (y < 0)
		{
			break;
		}
		else if (board[y * 8 + x] != nullptr)
		{
			if (board[y * 8 + x].get()->GetPlayer() != GetPlayer())
			{
				mPossibleMove.insert(y * 8 + x);
			}
			break;
		}
		else
		{
			mPossibleMove.insert(y * 8 + x);
		}
	}
}

const char * Rook::GetRole()
{
	return " R ";
}


