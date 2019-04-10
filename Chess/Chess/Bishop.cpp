#include "Bishop.h"

Bishop::Bishop(ePlayerType player, int position)
	: Piece(ePieceType::BISHOP, player, position)
{
}

const char * Bishop::GetRole()
{
	return " B ";
}

void Bishop::CalculateMove(const unique_ptr<Piece> board[])
{
	mPossibleMove.clear();
	mPossibleMove.insert(mPosition);
	int x = mPosition % 8;
	int y = mPosition / 8;
	while (true)
	{
		x++;
		y++;
		if (x > 7 || y > 7)
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
		y--;
		if (x < 0 || y < 0)
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
		x++;
		y--;
		if (x > 7 || y < 0)
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
		y++;
		if (x < 0 || y > 7)
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
