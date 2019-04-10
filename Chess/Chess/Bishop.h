#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop() = delete;
	Bishop(ePlayerType player, int position);

	virtual const char * GetRole() override;

	// Piece을(를) 통해 상속됨
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};
