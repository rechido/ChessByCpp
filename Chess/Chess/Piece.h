#pragma once
#include "Common.h"

using namespace std;

enum ePieceType
{
	PAWN,
	ROOK,
	BISHOP,
	KNIGHT,
	QUEEN,
	KING
};

enum ePlayerType
{
	BLACK,
	WHITE
};

class Piece
{
public:
	Piece() = delete;
	Piece(ePieceType piece, ePlayerType player, int position);
	virtual ~Piece() = default;
	virtual void CalculateMove(const unique_ptr<Piece> board[]) = 0;
	void AddMove(int position);
	void SubstractMove(int position);
	ePieceType GetType() const;
	ePlayerType GetPlayer() const;
	set<int> GetPossibleMove() const;
	size_t GetPossibleMoveCount() const;
	int GetPosition() const;
	void SetPosition(int position);
	virtual const char* GetRole() = 0;
	bool IsMoved();
	void SetMoved();
	string ToString();
protected:
	ePieceType mType;
	ePlayerType mPlayer;
	set<int> mPossibleMove;
	int mPosition;
	bool bIsMoved;
};
