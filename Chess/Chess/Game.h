#pragma once

#include "Common.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"

#define BLACK_WHITE 15
#define BLUE_BLACK 144
#define BLUE_WHITE 159
#define PURPLE_BLACK 208
#define PURPLE_WHITE 223
#define GREEN_BLACK 160
#define GREEN_WHITE 175
#define RED_BLACK 192
#define RED_WHITE 207
#define YELLOW_BLACK 224
#define YELLOW_WHITE 239

using namespace std;

struct PrintInfo
{
	int mColor;
	const char* mPieceOrBlank;
};

class Game
{
public:
	Game() = delete;
	Game(unique_ptr<Piece> board[]);
	Game(const Game& other) = delete;
	~Game();

	void Draw();
	void Clear();
	void WaitForKeyInput();
	void Print();
	bool Key_pressed(int key);
	void Grab();
	void Put();
	ePieceType SelectPromotion();
	void DrawPromotionMenu(int select);
	void CalculateMove(unique_ptr<Piece> board[]);
	bool CheckChecked(unique_ptr<Piece> board[], ePlayerType player);
	bool SimulateCheck(int startPosition, int endPosition, unique_ptr<Piece> board[], ePlayerType player);
	bool CheckCanBeUnChecked(ePlayerType player);
	bool CheckThisGridUnderAttackByEnemy(int position, ePlayerType enemy);
	bool CheckStalemate();
	void ChangeTurn();
	unique_ptr<Piece>* CopyBoard(unique_ptr<Piece> board[]);
	void EnPassant();

	void ActionLeft();
	void ActionRight();
	void ActionUp();
	void ActionDown();
	void ActionEnter();

private:

	HANDLE mHConsole;
	PrintInfo mPrintInfo[64];
	unique_ptr<Piece>* mBoard;
	unique_ptr<Piece> mGrab;
	int mPositionNow;
	ePlayerType mTurn;
	bool bIsChecked;
	bool bIsCheckmate;
	bool bIsStalemate;
	bool bWarningForCheck;
	int mEnPassant; // -1 if nothing, 0~63
};
