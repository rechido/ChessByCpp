#pragma once

#include "Common.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"

class Simulator
{
public:
	Simulator() = delete;
	Simulator(unique_ptr<Piece> board[]);
	bool CheckCanbeUnChecked();
	int Simulate();

private:
	unique_ptr<Piece> mBoard[64];
};