#include "Pawn.h"

Pawn::Pawn(ePlayerType player, int position)
	: Piece(ePieceType::PAWN, player, position)
{
}

const char * Pawn::GetRole()
{
	return " P ";
}

void Pawn::CalculateMove(const unique_ptr<Piece> board[])
{
	mPossibleMove.clear();
	mPossibleMove.insert(mPosition);
	int x = mPosition % 8;
	int y = mPosition / 8;
	if (mPlayer == ePlayerType::WHITE)
	{
		y--;
		if (y >= 0 && board[y * 8 + x] == nullptr)
		{
			mPossibleMove.insert(y * 8 + x);
		}
		if (!bIsMoved && board[y * 8 + x] == nullptr)
		{
			y--;
			if (y >= 0 && board[y * 8 + x] == nullptr)
			{
				mPossibleMove.insert(y * 8 + x);
			}
		}
	}
	else
	{
		y++;
		if (y <= 7 && board[y * 8 + x] == nullptr)
		{
			mPossibleMove.insert(y * 8 + x);
		}
		if (!bIsMoved && board[y * 8 + x] == nullptr)
		{
			y++;
			if (y <= 7 && board[y * 8 + x] == nullptr)
			{
				mPossibleMove.insert(y * 8 + x);
			}
		}
	}
	y = mPosition / 8;
	if (mPlayer == ePlayerType::WHITE)
	{
		y--;
	}
	else
	{
		y++;
	}
	x++;
	if (x <= 7 && board[y * 8 + x] != nullptr && board[y * 8 + x].get()->GetPlayer() != GetPlayer())
	{
		mPossibleMove.insert(y * 8 + x);
	}
	x -= 2;
	if (x >= 0 && board[y * 8 + x] != nullptr && board[y * 8 + x].get()->GetPlayer() != GetPlayer())
	{
		mPossibleMove.insert(y * 8 + x);
	}
}
