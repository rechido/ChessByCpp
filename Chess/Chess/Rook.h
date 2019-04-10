#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook() = delete;
	Rook(ePlayerType player, int position);

	// Piece��(��) ���� ��ӵ�
	virtual const char * GetRole() override;

	// Piece��(��) ���� ��ӵ�
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};