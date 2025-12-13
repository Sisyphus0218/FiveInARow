#pragma once

#include <algorithm>
#include <vector>
#include "ChessBoard.h"
#include "Head.h"
#include "Stone.h"

class Judge
{
public:
	Judge() = default;
	~Judge() = default;

	int ChessPattern(std::vector<int> window, int myColor);
	int IsLiveThree(std::vector<int> line, int color);
	int IsFour(std::vector<int> line, int color);
	int IsFive(std::vector<int> line, int color);
	int IsOverline(std::vector<int> line, int color);

	int CheckDoubleThreeForbidden(ChessBoard board, int color, Stone currentStep);
	int CheckDoubleFourForbidden(ChessBoard board, int color, Stone currentStep);
	int CheckOverlineForbidden(ChessBoard board, int color, Stone currentStep);

	int CheckFive(ChessBoard board, int color, Stone currentStep);
	int JudgeForbidden(ChessBoard board, int color, Stone currentStep);
	int JudgeBoard(ChessBoard board);
};

