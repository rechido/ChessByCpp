#include "Game.h"

Game::Game(unique_ptr<Piece> board[])
	: mHConsole(GetStdHandle(STD_OUTPUT_HANDLE))
	, mGrab(nullptr)
	, mPositionNow(0)
	, mTurn(ePlayerType::BLACK)
	, bIsChecked(false)
	, bIsCheckmate(false)
	, bIsStalemate(false)
	, bWarningForCheck(false)
	, mEnPassant(-1)
{
	mBoard = board;

	CalculateMove(mBoard);
	Draw();
	WaitForKeyInput();
}
Game::~Game()
{
	delete[] mBoard;
}

void Game::Draw()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* grab = mGrab.get();
			Piece* piece = mBoard[i * 8 + j].get();

			// set pieceType
			if (grab != nullptr && grab->GetPosition() == i * 8 + j)
			{
				mPrintInfo[i * 8 + j].mPieceOrBlank = grab->GetRole();
			}
			else if (piece != nullptr)
			{
				mPrintInfo[i * 8 + j].mPieceOrBlank = piece->GetRole();
			}
			else
			{
				mPrintInfo[i * 8 + j].mPieceOrBlank = "   ";
			}

			// set Color
			if (i * 8 + j == mPositionNow)
			{
				if (grab != nullptr && grab->GetPosition() == i * 8 + j && grab->GetPlayer() == ePlayerType::WHITE)
				{
					mPrintInfo[i * 8 + j].mColor = YELLOW_WHITE;
				}
				else if (piece != nullptr && piece->GetPlayer() == ePlayerType::WHITE)
				{
					mPrintInfo[i * 8 + j].mColor = YELLOW_WHITE;
				}
				else
				{
					mPrintInfo[i * 8 + j].mColor = YELLOW_BLACK;
				}
			}
			else if (grab != nullptr && grab->GetPosition() == i * 8 + j)
			{
				if (grab->GetPlayer() == ePlayerType::WHITE)
				{
					mPrintInfo[i * 8 + j].mColor = GREEN_WHITE;
				}
				else
				{
					mPrintInfo[i * 8 + j].mColor = GREEN_BLACK;
				}
			}
			else
			{
				bool IsGrabPossiblePosition = false;
				if (grab != nullptr)
				{
					for (int possiblePosition : grab->GetPossibleMove())
					{
						if (possiblePosition == i * 8 + j)
						{
							if (piece != nullptr && piece->GetPlayer() == ePlayerType::WHITE)
							{
								mPrintInfo[i * 8 + j].mColor = GREEN_WHITE;
							}
							else
							{
								mPrintInfo[i * 8 + j].mColor = GREEN_BLACK;
							}
							IsGrabPossiblePosition = true;
							break;
						}
					}
				}
				if (IsGrabPossiblePosition)
				{
					continue;
				}
				else if (i % 2 == 0)
				{
					if (j % 2 == 0)
					{
						if (piece != nullptr && piece->GetPlayer() == ePlayerType::WHITE)
						{
							mPrintInfo[i * 8 + j].mColor = BLUE_WHITE;
						}
						else
						{
							mPrintInfo[i * 8 + j].mColor = BLUE_BLACK;
						}
					}
					else
					{
						if (piece != nullptr &&  piece->GetPlayer() == ePlayerType::WHITE)
						{
							mPrintInfo[i * 8 + j].mColor = PURPLE_WHITE;
						}
						else
						{
							mPrintInfo[i * 8 + j].mColor = PURPLE_BLACK;
						}
					}
				}
				else
				{
					if (j % 2 == 0)
					{
						if (piece != nullptr &&  piece->GetPlayer() == ePlayerType::WHITE)
						{
							mPrintInfo[i * 8 + j].mColor = PURPLE_WHITE;
						}
						else
						{
							mPrintInfo[i * 8 + j].mColor = PURPLE_BLACK;
						}
					}
					else
					{
						if (piece != nullptr &&  piece->GetPlayer() == ePlayerType::WHITE)
						{
							mPrintInfo[i * 8 + j].mColor = BLUE_WHITE;
						}
						else
						{
							mPrintInfo[i * 8 + j].mColor = BLUE_BLACK;
						}
					}
				}
			}
		}
	}
	Print();

	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::string grab = (mGrab.get() == nullptr) ? "" : mGrab.get()->ToString();
	cout << "Grab : " << grab.c_str() << endl;
	const char* turn = (mTurn == ePlayerType::WHITE) ? "WHITE" : "BLACK";
	cout << "Turn : " << turn << endl;
	if (bIsCheckmate)
	{
		cout << "Checkmate" << endl;
	}
	else if (bIsChecked)
	{
		cout << "Check" << endl;
	}
	else if (bIsStalemate)
	{
		cout << "Stalemate" << endl;
	}
	if (bWarningForCheck)
	{
		cout << "You will be checked if you put there." << endl;
		bWarningForCheck = false;
	}
}

void Game::Clear()
{
	SetConsoleTextAttribute(mHConsole, 1);
	system("CLS");
}

void Game::WaitForKeyInput()
{
	while (true)
	{
		if (bIsCheckmate)
		{
			if (mTurn == ePlayerType::WHITE)
			{
				cout << "White";
			}
			else
			{
				cout << "Black";
			}
			cout << " Is Win!" << endl;
			break;
		}
		else if (bIsStalemate)
		{
			cout << "Draw!" << endl;
			break;
		}
		if (Key_pressed(VK_LEFT))
		{
			ActionLeft();
			Clear();
			Draw();
		}
		else if (Key_pressed(VK_UP))
		{
			ActionUp();
			Clear();
			Draw();
		}
		else if (Key_pressed(VK_DOWN))
		{
			ActionDown();
			Clear();
			Draw();
		}
		else if (Key_pressed(VK_RIGHT))
		{
			ActionRight();
			Clear();
			Draw();
		}
		else if (Key_pressed(VK_RETURN))
		{
			ActionEnter();
			Clear();
			Draw();
		}
		Sleep(100);
	}
}

void Game::Print()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			SetConsoleTextAttribute(mHConsole, mPrintInfo[i * 8 + j].mColor);
			cout << mPrintInfo[i * 8 + j].mPieceOrBlank;
		}
		cout << endl;
	}
	cout << endl;
}

bool Game::Key_pressed(int key)
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
}

void Game::Grab()
{
	Piece* piece = mBoard[mPositionNow].get();
	if (piece != nullptr && piece->GetPlayer() == mTurn)
	{
		mGrab = std::move(mBoard[mPositionNow]);
	}
}

void Game::Put()
{
	Piece* grab = mGrab.get();
	// castling
	if (grab->GetType() == ePieceType::KING)
	{
		if (!grab->IsMoved())
		{
			if (grab->GetPlayer() == ePlayerType::WHITE)
			{
				if (mPositionNow == 58)
				{
					grab->SetPosition(58);
					mBoard[58] = std::move(mGrab);
					mBoard[58].get()->SetMoved();
					mBoard[56].get()->SetPosition(59);
					mBoard[59] = std::move(mBoard[56]);
					mBoard[59].get()->SetMoved();
					CalculateMove(mBoard);
					ChangeTurn();
					return;
				}
				else if (mPositionNow == 62)
				{
					grab->SetPosition(62);
					mBoard[62] = std::move(mGrab);
					mBoard[62].get()->SetMoved();
					mBoard[63].get()->SetPosition(61);
					mBoard[61] = std::move(mBoard[63]);
					mBoard[61].get()->SetMoved();
					CalculateMove(mBoard);
					ChangeTurn();
					return;
				}
			}
			else
			{
				if (mPositionNow == 2)
				{
					grab->SetPosition(2);
					mBoard[2] = std::move(mGrab);
					mBoard[2].get()->SetMoved();
					mBoard[0].get()->SetPosition(3);
					mBoard[3] = std::move(mBoard[0]);
					mBoard[3].get()->SetMoved();
					CalculateMove(mBoard);
					ChangeTurn();
					return;
				}
				else if (mPositionNow == 6)
				{
					grab->SetPosition(6);
					mBoard[6] = std::move(mGrab);
					mBoard[6].get()->SetMoved();
					mBoard[7].get()->SetPosition(5);
					mBoard[5] = std::move(mBoard[7]);
					mBoard[5].get()->SetMoved();
					CalculateMove(mBoard);
					ChangeTurn();
					return;
				}
			}
		}
	}
	// pawn promotion
	int y = mPositionNow / 8;
	if (grab->GetType() == ePieceType::PAWN && grab->GetPlayer() == ePlayerType::WHITE && y == 0)
	{
		mBoard[mPositionNow] = std::move(mGrab);
		ePieceType promotion = SelectPromotion();
		switch (promotion)
		{
		case ePieceType::QUEEN:
			mBoard[mPositionNow] = std::make_unique<Queen>(ePlayerType::WHITE, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::ROOK:
			mBoard[mPositionNow] = std::make_unique<Rook>(ePlayerType::WHITE, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::BISHOP:
			mBoard[mPositionNow] = std::make_unique<Bishop>(ePlayerType::WHITE, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::KNIGHT:
			mBoard[mPositionNow] = std::make_unique<Knight>(ePlayerType::WHITE, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		}
		CalculateMove(mBoard);
		ePlayerType enemy = (mTurn == ePlayerType::WHITE ? ePlayerType::BLACK : ePlayerType::WHITE);
		bIsChecked = CheckChecked(mBoard, enemy);
		if (bIsChecked && !CheckCanBeUnChecked(enemy))
		{
			bIsCheckmate = true;
			return;
		}
		ChangeTurn();
		return;
	}
	else if (grab->GetType() == ePieceType::PAWN && grab->GetPlayer() == ePlayerType::BLACK && y == 7)
	{
		mBoard[mPositionNow] = std::move(mGrab);
		ePieceType promotion = SelectPromotion();
		switch (promotion)
		{
		case ePieceType::QUEEN:
			mBoard[mPositionNow] = std::make_unique<Queen>(ePlayerType::BLACK, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::ROOK:
			mBoard[mPositionNow] = std::make_unique<Rook>(ePlayerType::BLACK, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::BISHOP:
			mBoard[mPositionNow] = std::make_unique<Bishop>(ePlayerType::BLACK, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		case ePieceType::KNIGHT:
			mBoard[mPositionNow] = std::make_unique<Knight>(ePlayerType::BLACK, mPositionNow);
			mBoard[mPositionNow].get()->SetMoved();
			break;
		}
		CalculateMove(mBoard);
		ePlayerType enemy = (mTurn == ePlayerType::WHITE ? ePlayerType::BLACK : ePlayerType::WHITE);
		bIsChecked = CheckChecked(mBoard, enemy);
		if (bIsChecked && !CheckCanBeUnChecked(enemy))
		{
			bIsCheckmate = true;
			return;
		}
		ChangeTurn();
		return;
	}
	// En passant
	if (mEnPassant != -1)
	{
		int xEp = mEnPassant % 8;
		int yEp = mEnPassant / 8;
		int xNow = mPositionNow % 8;
		int yNow = mPositionNow / 8;

		if (grab->GetPlayer() == ePlayerType::WHITE)
		{
			yEp--;
		}
		else
		{
			yEp++;
		}

		if (grab->GetType() == ePieceType::PAWN)
		{
			if (xEp == xNow && yEp == yNow)
			{
				mBoard[mPositionNow] = std::move(mBoard[mEnPassant]);
				grab->SetPosition(mPositionNow);
				mBoard[mPositionNow] = std::move(mGrab);
				CalculateMove(mBoard);
				ePlayerType enemy = (mTurn == ePlayerType::WHITE ? ePlayerType::BLACK : ePlayerType::WHITE);
				bIsChecked = CheckChecked(mBoard, enemy);
				if (bIsChecked && !CheckCanBeUnChecked(enemy))
				{
					bIsCheckmate = true;
				}
				ChangeTurn();
				mEnPassant = -1;
				return;
			}
		}
		mEnPassant = -1;
	}
	if (grab->GetType() == ePieceType::PAWN && !grab->IsMoved())
	{
		int xPrev = grab->GetPosition() % 8;
		int yPrev = grab->GetPosition() / 8;
		int xNow = mPositionNow % 8;
		int yNow = mPositionNow / 8;

		if ((grab->GetPlayer() == ePlayerType::WHITE && xPrev == xNow && yPrev - 2 == yNow)
			|| (grab->GetPlayer() == ePlayerType::BLACK && xPrev == xNow && yPrev + 2 == yNow))
		{
			mEnPassant = mPositionNow;
			grab->SetPosition(mPositionNow);
			mBoard[mPositionNow] = std::move(mGrab);
			mBoard[mPositionNow].get()->SetMoved();
			CalculateMove(mBoard);
			if (xNow - 1 >= 0)
			{
				Piece* piece = mBoard[yNow * 8 + xNow - 1].get();
				if (piece != nullptr && piece->GetType() == ePieceType::PAWN && piece->GetPlayer() != grab->GetPlayer())
				{
					int yEp = (yPrev + yNow) / 2;
					piece->AddMove(yEp * 8 + xNow);
				}
			}
			if (xNow + 1 <= 7)
			{
				Piece* piece = mBoard[yNow * 8 + xNow + 1].get();
				if (piece != nullptr && piece->GetType() == ePieceType::PAWN && piece->GetPlayer() != grab->GetPlayer())
				{
					int yEp = (yPrev + yNow) / 2;
					piece->AddMove(yEp * 8 + xNow);
				}
			}
			ePlayerType enemy = (mTurn == ePlayerType::WHITE ? ePlayerType::BLACK : ePlayerType::WHITE);
			bIsChecked = CheckChecked(mBoard, enemy);
			if (bIsChecked && !CheckCanBeUnChecked(enemy))
			{
				bIsCheckmate = true;
				return;
			}
			ChangeTurn();
			return;
		}
	}

	// normal move
	int positionPrev = grab->GetPosition();
	grab->SetPosition(mPositionNow);
	mBoard[mPositionNow] = std::move(mGrab);
	if (positionPrev != mPositionNow)
	{
		mBoard[mPositionNow].get()->SetMoved();
		CalculateMove(mBoard);
		ePlayerType enemy = (mTurn == ePlayerType::WHITE ? ePlayerType::BLACK : ePlayerType::WHITE);
		bIsChecked = CheckChecked(mBoard, enemy);
		if (bIsChecked && !CheckCanBeUnChecked(enemy))
		{
			bIsCheckmate = true;
			return;
		}
		ChangeTurn();
		return;
	}
}

ePieceType Game::SelectPromotion()
{
	int select = 1;
	Clear();
	DrawPromotionMenu(select);
	while (true)
	{
		if (Key_pressed(VK_LEFT))
		{
			if (select >= 1)
			{
				select--;
				Clear();
				DrawPromotionMenu(select);
			}
		}
		else if (Key_pressed(VK_RIGHT))
		{
			if (select <= 4)
			{
				select++;
				Clear();
				DrawPromotionMenu(select);
			}
		}
		else if (Key_pressed(VK_RETURN))
		{
			switch (select)
			{
			case 1:
				return ePieceType::QUEEN;
			case 2:
				return ePieceType::ROOK;
			case 3:
				return ePieceType::BISHOP;
			case 4:
				return ePieceType::KNIGHT;
			}
		}
		Sleep(100);
	}
}

void Game::DrawPromotionMenu(int select)
{
	if (select == 1)
	{
		SetConsoleTextAttribute(mHConsole, RED_WHITE);
		cout << "QUEEN";
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
		cout << "QUEEN";
	}
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	cout << " ";
	if (select == 2)
	{
		SetConsoleTextAttribute(mHConsole, RED_WHITE);
		cout << "ROOK";
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
		cout << "ROOK";
	}
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	cout << " ";
	if (select == 3)
	{
		SetConsoleTextAttribute(mHConsole, RED_WHITE);
		cout << "BISHOP";
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
		cout << "BISHOP";
	}
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	cout << " ";
	if (select == 4)
	{
		SetConsoleTextAttribute(mHConsole, RED_WHITE);
		cout << "KNIGHT";
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
		cout << "KNIGHT";
	}
}

void Game::CalculateMove(unique_ptr<Piece> board[])
{
	// first step : add all possible moves
	for (int i = 0; i < 64; i++)
	{
		Piece* piece = board[i].get();
		if (piece != nullptr)
		{
			piece->CalculateMove(board);
		}
	}

	// second step : add castling moves
	if (!bIsChecked) // castling never be done while somebody are under check
	{
		if (board[60] != nullptr) // set castling for white king
		{
			Piece* piece = board[60].get();
			if (piece != nullptr && piece->GetType() == ePieceType::KING && piece->GetPlayer() == ePlayerType::WHITE && !piece->IsMoved())
			{
				Piece* rook = board[56].get();
				if (rook != nullptr && rook->GetType() == ePieceType::ROOK && rook->GetPlayer() == piece->GetPlayer() && !rook->IsMoved())
				{
					if (board[57] == nullptr && board[58] == nullptr && board[59] == nullptr
						&& !CheckThisGridUnderAttackByEnemy(57, ePlayerType::BLACK)
						&& !CheckThisGridUnderAttackByEnemy(58, ePlayerType::BLACK)
						&& !CheckThisGridUnderAttackByEnemy(59, ePlayerType::BLACK))
					{
						piece->AddMove(58);
					}
				}
				rook = board[63].get();
				if (rook != nullptr && rook->GetType() == ePieceType::ROOK && rook->GetPlayer() == piece->GetPlayer() && !rook->IsMoved())
				{
					if (board[61] == nullptr && board[62] == nullptr
						&& !CheckThisGridUnderAttackByEnemy(61, ePlayerType::BLACK)
						&& !CheckThisGridUnderAttackByEnemy(62, ePlayerType::BLACK))
					{
						piece->AddMove(62);
					}
				}
			}
		}
		if (board[4] != nullptr) // set castling for black king
		{
			Piece* piece = board[4].get();
			if (piece != nullptr && piece->GetType() == ePieceType::KING && piece->GetPlayer() == ePlayerType::BLACK && !piece->IsMoved())
			{
				Piece* rook = board[0].get();
				if (rook != nullptr && rook->GetType() == ePieceType::ROOK && rook->GetPlayer() == piece->GetPlayer() && !rook->IsMoved())
				{
					if (board[1] == nullptr && board[2] == nullptr && board[3] == nullptr
						&& !CheckThisGridUnderAttackByEnemy(1, ePlayerType::WHITE)
						&& !CheckThisGridUnderAttackByEnemy(2, ePlayerType::WHITE)
						&& !CheckThisGridUnderAttackByEnemy(3, ePlayerType::WHITE))
					{
						piece->AddMove(2);
					}
				}
				rook = board[7].get();
				if (rook != nullptr && rook->GetType() == ePieceType::ROOK && rook->GetPlayer() == piece->GetPlayer() && !rook->IsMoved())
				{
					if (board[5] == nullptr && board[6] == nullptr
						&& !CheckThisGridUnderAttackByEnemy(5, ePlayerType::WHITE)
						&& !CheckThisGridUnderAttackByEnemy(6, ePlayerType::WHITE))
					{
						piece->AddMove(6);
					}
				}
			}
		}
	}
}

bool Game::CheckChecked(unique_ptr<Piece> board[], ePlayerType player)
{
	for (int i = 0; i < 64; i++)
	{
		Piece* piece = board[i].get();
		if (piece != nullptr)
		{
			for (int possibleMove : piece->GetPossibleMove())
			{
				Piece* target = board[possibleMove].get();
				if (target != nullptr && target->GetType() == ePieceType::KING && target->GetPlayer() != piece->GetPlayer() && target->GetPlayer() == player)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::SimulateCheck(int startPosition, int endPosition, unique_ptr<Piece> board[], ePlayerType player)
{
	unique_ptr<Piece>* copyBoard = CopyBoard(board);
	copyBoard[startPosition].get()->SetPosition(endPosition);
	copyBoard[endPosition] = std::move(copyBoard[startPosition]);
	CalculateMove(copyBoard);
	bool isChecked = CheckChecked(copyBoard, player);
	delete[] copyBoard;
	return isChecked;
}

bool Game::CheckCanBeUnChecked(ePlayerType player)
{
	for (int i = 0; i < 64; i++)
	{
		Piece* piece = mBoard[i].get();
		if (piece != nullptr && piece->GetPlayer() == player)
		{
			for (int possibleMove : piece->GetPossibleMove())
			{
				if (!SimulateCheck(i, possibleMove, mBoard, player))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::CheckThisGridUnderAttackByEnemy(int position, ePlayerType enemy)
{
	for (int i = 0; i < 64; i++)
	{
		Piece* piece = mBoard[i].get();
		if (piece != nullptr && piece->GetPlayer() == enemy)
		{
			for (int possibleMove : piece->GetPossibleMove())
			{
				if (possibleMove == position)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::CheckStalemate()
{
	if (!bIsChecked)
	{
		for (int i = 0; i < 64; i++)
		{
			Piece* piece = mBoard[i].get();
			if (piece != nullptr && piece->GetPlayer() == mTurn)
			{
				for (int possibleMove : piece->GetPossibleMove())
				{
					if (possibleMove != i && !SimulateCheck(i, possibleMove, mBoard, mTurn))
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;
}

void Game::ChangeTurn()
{
	if (mTurn == ePlayerType::WHITE)
	{
		mTurn = ePlayerType::BLACK;
	}
	else
	{
		mTurn = ePlayerType::WHITE;
	}
}

unique_ptr<Piece>* Game::CopyBoard(unique_ptr<Piece> board[])
{
	unique_ptr<Piece>* copyBoard = new unique_ptr<Piece>[64];
	for (int i = 0; i < 64; i++)
	{
		if (board[i] != nullptr)
		{
			Piece* piece = board[i].get();
			switch (piece->GetType())
			{
			case ePieceType::ROOK:
				copyBoard[i] = std::make_unique<Rook>(piece->GetPlayer(), i);
				break;
			case ePieceType::BISHOP:
				copyBoard[i] = std::make_unique<Bishop>(piece->GetPlayer(), i);
				break;
			case ePieceType::KNIGHT:
				copyBoard[i] = std::make_unique<Knight>(piece->GetPlayer(), i);
				break;
			case ePieceType::QUEEN:
				copyBoard[i] = std::make_unique<Queen>(piece->GetPlayer(), i);
				break;
			case ePieceType::KING:
				copyBoard[i] = std::make_unique<King>(piece->GetPlayer(), i);
				break;
			case ePieceType::PAWN:
				copyBoard[i] = std::make_unique<Pawn>(piece->GetPlayer(), i);
				break;
			}
		}
	}
	return copyBoard;
}

void Game::EnPassant()
{
}

void Game::ActionLeft()
{
	int x = mPositionNow % 8;
	int y = mPositionNow / 8;
	if (x > 0)
	{
		x--;
	}
	mPositionNow = y * 8 + x;
}

void Game::ActionRight()
{
	int x = mPositionNow % 8;
	int y = mPositionNow / 8;
	if (x < 7)
	{
		x++;
	}
	mPositionNow = y * 8 + x;
}

void Game::ActionUp()
{
	int x = mPositionNow % 8;
	int y = mPositionNow / 8;
	if (y > 0)
	{
		y--;
	}
	mPositionNow = y * 8 + x;
}

void Game::ActionDown()
{
	int x = mPositionNow % 8;
	int y = mPositionNow / 8;
	if (y < 7)
	{
		y++;
	}
	mPositionNow = y * 8 + x;
}

void Game::ActionEnter()
{
	if (mGrab == nullptr)
	{
		Grab();
	}
	else
	{
		for (int possiblePosition : mGrab->GetPossibleMove())
		{
			if (mPositionNow == possiblePosition)
			{
				int positionPrev = mGrab.get()->GetPosition();
				mBoard[positionPrev] = std::move(mGrab);
				if (SimulateCheck(positionPrev, mPositionNow, mBoard, mTurn))
				{
					bWarningForCheck = true;
					mGrab = std::move(mBoard[positionPrev]);
					return;
				}
				mGrab = std::move(mBoard[positionPrev]);
				Put();
				bIsStalemate = CheckStalemate();
				return;
			}
		}
	}
}
