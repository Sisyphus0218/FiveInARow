#include "Display.h"

using namespace std;

void Display::DisplayIntersection(int size, int i, int j)
{
	if (i == 0) {
		if (j == 0)
		{
			cout << "©°";
		}
		else if (j == size - 1)
		{
			cout << "©´";
		}
		else
		{
			cout << "©Ð";
		}
	}
	else if (i == size - 1) {
		if (j == 0)
		{
			cout << "©¸";
		}
		else if (j == size - 1)
		{
			cout << "©¼";
		}
		else
		{
			cout << "©Ø";
		}
	}
	else {
		if (j == 0)
		{
			printf("©À");
		}
		else if (j == size - 1)
		{
			printf("©È");
		}
		else
		{
			printf("©à");
		}
	}
}

void Display::DisplayRowNumber(int num)
{
	num = 15 - num;
	if (num >= 0 && num <= 9)
	{
		cout << " " << num;
	}
	else if (num >= 10 && num <= 15)
	{
		cout << num;
	}
}

void Display::DisplayColumnLetter()
{
	cout << "  " << "ABCDEFGHIJKLMKO" << endl;
}

void Display::DisplayStone(Stone currentStep, int color, int i, int j)
{
	if (i == currentStep.GetRowIdx() && j == currentStep.GetColumnIdx())
	{
		if (color == BLACK)
		{
			cout << "¡ø";
		}
		else if (color == WHITE)
		{
			cout << "¡÷";
		}
	}
	else
	{
		if (color == BLACK)
		{
			cout << "¡ñ";
		}
		else if (color == WHITE)
		{
			cout << "¡ð";
		}
	}
}

void Display::DisplayChessboard(ChessBoard board)
{
	int size = board.GetBoardSize();
	Stone currentStep = board.GetCurrentStep();

	for (int i = 0; i < size; i++)
	{
		DisplayRowNumber(i);
		for (int j = 0; j < size; j++)
		{
			int result = board.GetAt({ i, j });
			switch (result)
			{
			case EMPTY:
				DisplayIntersection(size, i, j);
				break;

			case BLACK:
				DisplayStone(currentStep, BLACK, i, j);
				break;

			case WHITE:
				DisplayStone(currentStep, WHITE, i, j);
				break;
			}
		}
		cout << endl;
	}
	DisplayColumnLetter();
	cout << endl;
}

int Display::DisplayMainMenu()
{
	cout << "==================================" << endl;
	cout << "          Five In A Row           " << endl;
	cout << "==================================" << endl;
	cout << "1. PVP (Player vs Player)" << endl;
	cout << "2. PVE (Player vs AI)" << endl;
	cout << "Please select (1-2): ";

	string input;
	int mode;

	while (true)
	{
		cin >> input;

		try
		{
			mode = stoi(input);
			if (mode == 1 || mode == 2)
			{
				return mode;
			}
			else
			{
				cout << "Invalid input! Please enter 1 or 2: ";
			}
		}
		catch (...)
		{
			cout << "Invalid input! Please enter 1 or 2: ";
		}
	}
}

int Display::DisplaySetup()
{
	system("cls");
	cout << "==================================" << endl;
	cout << "            Game Setup            " << endl;
	cout << "==================================" << endl;
	cout << "Choose your role:" << endl;
	cout << "1. Play as Black (First player)" << endl;
	cout << "2. Play as White (Second player)" << endl;
	cout << "Please select (1-2): ";

	while (true)
	{
		string input;
		int choice;

		while (true)
		{
			cin >> input;

			try
			{
				choice = stoi(input);
				if (choice == 1)
				{
					cout << endl;
					cout << "You: BLACK ¡ñ| AI: WHITE ¡ð" << endl;
					cout << "You go first." << endl;
					cout << "Press Enter to continue: ";
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin.get();
					return choice;
				}
				else if (choice == 2)
				{
					cout << endl;
					cout << "AI: BLACK ¡ñ | You: WHITE ¡ð" << endl;
					cout << "AI goes first." << endl;
					cout << "Press Enter to continue: ";
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin.get();
					return choice;
				}
				else
				{
					cout << "Invalid input! Please enter 1 or 2: ";
				}
			}
			catch (...)
			{
				cout << "Invalid input! Please enter 1 or 2: ";
			}
		}
	}
}

void Display::DisplayCurrentStep(BoardCoord black, BoardCoord white)
{
	cout << "Current Step: " << endl;
	if (black.IsValid())
	{
		BoardNotation notation = black.ToNotation();
		cout << "Black: " << notation.GetColChar() << notation.GetRowNum() << endl;
	}
	else
	{
		cout << "Black: empty" << endl;
	}
	if (white.IsValid())
	{
		BoardNotation notation = white.ToNotation();
		cout << "White: " << notation.GetColChar() << notation.GetRowNum() << endl;
	}
	else
	{
		cout << "White: empty" << endl;
	}
	cout << endl;
}

void Display::DisplayJudgement(ChessBoard board, int result)
{
	int color = board.GetCurrentStep().GetColor();

	if (result == WIN)
	{
		if (color == BLACK)
		{
			cout << "Black wins!" << endl;
		}
		else if (color == WHITE)
		{
			cout << "White wins!" << endl;
		}
	}
	else if (result == FORBIDDEN_DOUBLE_THREE)
	{
		cout << "Double Three Forbidden!" << endl;
	}
	else if (result == FORBIDDEN_DOUBLE_FOUR)
	{
		cout << "Double Four Forbidden!" << endl;
	}
	else if (result == FORBIDDEN_OVERLINE)
	{
		cout << "Overline Forbidden!" << endl;
	}
}

void Display::DisplayCurrentInfo(ChessBoard board, BoardCoord black, BoardCoord white, int result)
{
	system("cls");
	DisplayChessboard(board);
	DisplayCurrentStep(black, white);
	DisplayJudgement(board, result);
}

