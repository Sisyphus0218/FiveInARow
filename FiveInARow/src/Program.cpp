#include "Program.h"

using namespace std;

Program::Program()
{
	display = new Display();

	mode = display->DisplayMainMenu();
	if (mode == MODE_PVP)
	{
		blackPlayer = new HumanPlayer(BLACK);
		whitePlayer = new HumanPlayer(WHITE);
	}
	else
	{
		int humanColor = display->DisplaySetup();
		if (humanColor == BLACK)
		{
			blackPlayer = new HumanPlayer(BLACK);
			whitePlayer = new AIPlayer(WHITE);
		}
		else
		{
			blackPlayer = new AIPlayer(BLACK);
			whitePlayer = new HumanPlayer(WHITE);
		}
	}

	judge = new Judge();
	chessBoard = new ChessBoard();

	currentBlackCoord = BoardCoord(-1, -1);
	currentWhiteCoord = BoardCoord(-1, -1);

	currentStep = 0;
}

Program::~Program()
{
	delete display;
	delete blackPlayer;
	delete whitePlayer;
	delete judge;
	delete chessBoard;
}

int Program::SaveMoveHistory()
{
	ofstream file;
	file.open("./move_history.txt");

	for (const auto& stone : blackMoveHistory)
	{
		BoardCoord coord = stone.GetCoord();
		BoardNotation notation = coord.ToNotation();
		char colChar = notation.GetColChar();
		int rowNum = notation.GetRowNum();

		file << colChar << rowNum << endl;
	}

	file << endl;

	for (const auto& stone : whiteMoveHistory)
	{
		BoardCoord coord = stone.GetCoord();
		BoardNotation notation = coord.ToNotation();
		char colChar = notation.GetColChar();
		int rowNum = notation.GetRowNum();

		file << colChar << rowNum << endl;
	}

	file.close();
	return 0;
}

int Program::StartGame()
{
	int result = 0;

	display->DisplayCurrentInfo(*chessBoard, currentBlackCoord, currentWhiteCoord, result);

	while (currentStep < MAXSTEP)
	{
		currentBlackCoord = blackPlayer->DecideNextStep(*chessBoard);
		blackMoveHistory.push_back(Stone(BLACK, currentBlackCoord));
		chessBoard->PlaceStone(BLACK, currentBlackCoord);
		result = judge->JudgeBoard(*chessBoard);
		display->DisplayCurrentInfo(*chessBoard, currentBlackCoord, currentWhiteCoord, result);
		if (result == WIN)
		{
			SaveMoveHistory();
			return 0;
		}
		currentStep++;

		currentWhiteCoord = whitePlayer->DecideNextStep(*chessBoard);
		whiteMoveHistory.push_back(Stone(WHITE, currentWhiteCoord));
		chessBoard->PlaceStone(WHITE, currentWhiteCoord);
		result = judge->JudgeBoard(*chessBoard);
		display->DisplayCurrentInfo(*chessBoard, currentBlackCoord, currentWhiteCoord, result);
		if (result == WIN)
		{
			SaveMoveHistory();
			return 0;
		}
		currentStep++;
	}

	cout << "The game ended in a tie." << endl;

	return 0;
}
