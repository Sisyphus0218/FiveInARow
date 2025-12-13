#pragma once

#include <algorithm>
#include <climits>
#include <vector>
#include "BoardCoord.h"
#include "ChessBoard.h"
#include "Head.h"
#include "Player.h"

class AIPlayer : public Player
{
public:
	AIPlayer();
	AIPlayer(int color);
	~AIPlayer() = default;

	std::vector<BoardCoord> GenerateCandidateMoves(ChessBoard& board);
	int ScorePattern(std::vector<int> window, int color);
	int EvaluateLine(std::vector<int> vec, int color);
	double EvaluateBoard(ChessBoard& board);
	double AlphaBetaPruning(ChessBoard* board, int depth, double alpha, double beta, bool is_max);
	BoardCoord DecideNextStep(ChessBoard& board);
};

