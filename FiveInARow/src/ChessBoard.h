#pragma once

#include <iostream>
#include <vector>
#include "BoardCoord.h"
#include "BoardNotation.h"
#include "Head.h"
#include "Stone.h"

class ChessBoard
{
private:
	static const int SIZE = 15;
	int chessBoard[SIZE][SIZE] = { 0 };
	std::vector<Stone> moveHistory;

public:
	ChessBoard() = default;
	~ChessBoard() = default;

	void SetAt(int color, BoardCoord coord);
	int GetAt(BoardCoord coord);

	void PlaceStone(int color, BoardCoord coord);
	void RemoveStone();

	Stone GetCurrentStep();
	int GetBoardSize();
	int GetStepNum();
	int IsEmptyAt(BoardCoord coord);
};

