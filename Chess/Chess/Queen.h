#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen() = delete;
	Queen(ePlayerType player, int position);

	// Piece��(��) ���� ��ӵ�
	virtual const char * GetRole() override;

	// Piece��(��) ���� ��ӵ�
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};