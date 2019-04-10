#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight() = delete;
	Knight(ePlayerType player, int position);

	virtual const char * GetRole() override;

	// Piece을(를) 통해 상속됨
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};
