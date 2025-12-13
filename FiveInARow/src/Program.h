#pragma once

#include <fstream>
#include "AIPlayer.h"
#include "ChessBoard.h"
#include "Display.h"
#include "Head.h"
#include "HumanPlayer.h"
#include "Judge.h"

class Program
{
private:
	const int MAXSTEP = 255;
	const int MODE_PVP = 1;
	const int MODE_PVE = 2;
	const int MODE_EXIT = 3;

	int currentStep;
	int mode;

	Display* display;
	Player* blackPlayer;
	Player* whitePlayer;
	Judge* judge;
	ChessBoard* chessBoard;

	BoardCoord currentBlackCoord;
	BoardCoord currentWhiteCoord;
	std::vector<Stone> blackMoveHistory;
	std::vector<Stone> whiteMoveHistory;

public:
	Program();
	~Program();

	int StartGame();
	int SaveMoveHistory();
};

