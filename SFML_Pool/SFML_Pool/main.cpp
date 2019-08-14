#include <iostream>
#include "Game.h"
#include "Board.h"

void test1()
{
	Board board(100, 100);
	Vector2f v1(1, 0);
	Vector2f v2 = board.rotate(90, v1);
	Vector2f v3 = board.rotate(45, v1);
	Vector2f v4 = board.rotate(-45, v1);
	Vector2f v5 = board.rotate(135, v1);
}

int main()
{
	Game Pool;
	Pool.run();

	//test1();

	return EXIT_SUCCESS;
}

