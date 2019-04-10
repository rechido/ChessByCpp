#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight() = delete;
	Knight(ePlayerType player, int position);

	virtual const char * GetRole() override;

	// Piece��(��) ���� ��ӵ�
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};
