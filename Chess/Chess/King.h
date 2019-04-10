#pragma once
#include "Piece.h"


class King : public Piece
{
	class Game;

public:
	King() = delete;
	King(ePlayerType player, int position);

	// Piece��(��) ���� ��ӵ�
	virtual const char * GetRole() override;

	// Piece��(��) ���� ��ӵ�
	virtual void CalculateMove(const unique_ptr<Piece> board[]) override;
};