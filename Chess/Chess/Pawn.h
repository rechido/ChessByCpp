#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn() = delete;
	Pawn(ePlayerType player, int position);

	// Piece을(를) 통해 상속됨
	virtual const char * GetRole() override;

	// Piece을(를) 통해 상속됨
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};