#include "Piece.h"

Piece::Piece(ePieceType piece, ePlayerType player, int position)
	: mType(piece)
	, mPlayer(player)
	, mPosition(position)
	, bIsMoved(false)
{
}

void Piece::AddMove(int position)
{
	mPossibleMove.insert(position);
}

void Piece::SubstractMove(int position)
{
	for (int possibleMove : mPossibleMove)
	{
		if (position == possibleMove)
		{
			mPossibleMove.erase(possibleMove);
			return;
		}
	}
}

ePieceType Piece::GetType() const
{
	return mType;
}

ePlayerType Piece::GetPlayer() const
{
	return mPlayer;
}
set<int> Piece::GetPossibleMove() const
{
	return mPossibleMove;
}

size_t Piece::GetPossibleMoveCount() const
{
	return mPossibleMove.size();
}

int Piece::GetPosition() const
{
	return mPosition;
}

void Piece::SetPosition(int position)
{
	mPosition = position;
}

bool Piece::IsMoved()
{
	return bIsMoved;
}

void Piece::SetMoved()
{
	bIsMoved = true;
}

string Piece::ToString()
{
	string str = "";
	str += "Piece=";
	switch (GetType())
	{
	case (ePieceType::ROOK):
		str += "ROOK";
		break;
	case (ePieceType::BISHOP):
		str += "BISHOP";
		break;
	case (ePieceType::KNIGHT):
		str += "KNIGHT";
		break;
	case (ePieceType::QUEEN):
		str += "QUEEN";
		break;
	case (ePieceType::KING):
		str += "KING";
		break;
	case (ePieceType::PAWN):
		str += "PAWN";
		break;
	}
	str += ", Player=";
	if (GetPlayer() == ePlayerType::WHITE)
	{
		str += "WHITE";
	}
	else
	{
		str += "BLACK";
	}
	return str;
}
