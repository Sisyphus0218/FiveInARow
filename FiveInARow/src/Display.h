#pragma once

#include <iostream>
#include <string>
#include "BoardCoord.h"
#include "BoardNotation.h"
#include "ChessBoard.h"
#include "Stone.h"

class Display
{
private:
	void DisplayIntersection(int size, int i, int j);
	void DisplayRowNumber(int num);
	void DisplayColumnLetter();
	void DisplayStone(Stone currentStep, int color, int i, int j);
	void DisplayChessboard(ChessBoard board);
	void DisplayCurrentStep(BoardCoord black, BoardCoord white);
	void DisplayJudgement(ChessBoard board, int result);

public:
	Display() = default;
	~Display() = default;

	int DisplayMainMenu();
	int DisplaySetup();
	void DisplayCurrentInfo(ChessBoard board, BoardCoord black, BoardCoord white, int result);
};

