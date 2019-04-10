#include <iostream>
#include <windows.h>   // WinApi header
#include <memory>
#include "Game.h"

using namespace std;

unique_ptr<Piece>* setGame1()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[64];
	board[0] = std::make_unique<Rook>(ePlayerType::BLACK, 0);
	board[1] = std::make_unique<Knight>(ePlayerType::BLACK, 1);
	board[2] = std::make_unique<Bishop>(ePlayerType::BLACK, 2);
	board[3] = std::make_unique<Queen>(ePlayerType::BLACK, 3);
	board[4] = std::make_unique<King>(ePlayerType::BLACK, 4);
	board[5] = std::make_unique<Bishop>(ePlayerType::BLACK, 5);
	board[6] = std::make_unique<Knight>(ePlayerType::BLACK, 6);
	board[7] = std::make_unique<Rook>(ePlayerType::BLACK, 7);
	board[8] = std::make_unique<Pawn>(ePlayerType::BLACK, 8);
	board[9] = std::make_unique<Pawn>(ePlayerType::BLACK, 9);
	board[10] = std::make_unique<Pawn>(ePlayerType::BLACK, 10);
	board[11] = std::make_unique<Pawn>(ePlayerType::BLACK, 11);
	board[12] = std::make_unique<Pawn>(ePlayerType::BLACK, 12);
	board[13] = std::make_unique<Pawn>(ePlayerType::BLACK, 13);
	board[14] = std::make_unique<Pawn>(ePlayerType::BLACK, 14);
	board[15] = std::make_unique<Pawn>(ePlayerType::BLACK, 15);

	board[56] = std::make_unique<Rook>(ePlayerType::WHITE, 56);
	board[57] = std::make_unique<Knight>(ePlayerType::WHITE, 57);
	board[58] = std::make_unique<Bishop>(ePlayerType::WHITE, 58);
	board[59] = std::make_unique<Queen>(ePlayerType::WHITE, 59);
	board[60] = std::make_unique<King>(ePlayerType::WHITE, 60);
	board[61] = std::make_unique<Bishop>(ePlayerType::WHITE, 61);
	board[62] = std::make_unique<Knight>(ePlayerType::WHITE, 62);
	board[63] = std::make_unique<Rook>(ePlayerType::WHITE, 63);
	board[48] = std::make_unique<Pawn>(ePlayerType::WHITE, 48);
	board[49] = std::make_unique<Pawn>(ePlayerType::WHITE, 49);
	board[50] = std::make_unique<Pawn>(ePlayerType::WHITE, 50);
	board[51] = std::make_unique<Pawn>(ePlayerType::WHITE, 51);
	board[52] = std::make_unique<Pawn>(ePlayerType::WHITE, 52);
	board[53] = std::make_unique<Pawn>(ePlayerType::WHITE, 53);
	board[54] = std::make_unique<Pawn>(ePlayerType::WHITE, 54);
	board[55] = std::make_unique<Pawn>(ePlayerType::WHITE, 55);

	return board;
}

unique_ptr<Piece>* setGame2()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[64];
	board[0] = std::make_unique<Rook>(ePlayerType::BLACK, 0);
	board[4] = std::make_unique<King>(ePlayerType::BLACK, 4);
	board[7] = std::make_unique<Rook>(ePlayerType::BLACK, 7);

	board[56] = std::make_unique<Rook>(ePlayerType::WHITE, 56);
	board[60] = std::make_unique<King>(ePlayerType::WHITE, 60);
	board[63] = std::make_unique<Rook>(ePlayerType::WHITE, 63);

	return board;
}

unique_ptr<Piece>* setGame3()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[64];
	board[3] = std::make_unique<Rook>(ePlayerType::BLACK, 3);
	board[34] = std::make_unique<King>(ePlayerType::BLACK, 34);

	board[36] = std::make_unique<King>(ePlayerType::WHITE, 36);

	return board;
}
unique_ptr<Piece>* setGame4()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[64];
	board[62] = std::make_unique<Rook>(ePlayerType::BLACK, 62);
	board[5] = std::make_unique<King>(ePlayerType::BLACK, 5);

	board[7] = std::make_unique<King>(ePlayerType::WHITE, 7);

	return board;
}

unique_ptr<Piece>* setGame5()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[64];
	board[35] = std::make_unique<Pawn>(ePlayerType::BLACK, 35);

	return board;
}

int main()
{
	//HANDLE mHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//for (int i = 0; i < 255; i++)
	//{
	//	SetConsoleTextAttribute(mHConsole, i);
	//	cout << i << " Hello " << endl;
	//}

	Game game(setGame1());
}