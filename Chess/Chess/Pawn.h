#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn() = delete;
	Pawn(ePlayerType player, int position);

	// Piece��(��) ���� ��ӵ�
	virtual const char * GetRole() override;

	// Piece��(��) ���� ��ӵ�
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};