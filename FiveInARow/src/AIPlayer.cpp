#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer()
	: Player()
{
	;
}

AIPlayer::AIPlayer(int color)
	: Player(color)
{
	;
}

vector<BoardCoord> AIPlayer::GenerateCandidateMoves(ChessBoard& board)
{
	vector<BoardCoord> candidateMoves;
	int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int i = 0; i < BOARD_SIZE; i++) // find the neighbors of existing pieces
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			BoardCoord coord(i, j);
			if (board.IsEmptyAt(coord))
			{
				bool hasNeighbor = false;
				for (int k = 0; k < 8; k++)
				{
					int ni = i + dx[k];
					int nj = j + dy[k];
					BoardCoord neightbor = BoardCoord(ni, nj);
					if (neightbor.IsValid() && !board.IsEmptyAt(neightbor))
					{
						hasNeighbor = true;
						break;
					}
				}
				if (hasNeighbor)
				{
					candidateMoves.push_back(coord);
				}
			}
		}
	}
	return candidateMoves;
}

int AIPlayer::ScorePattern(vector<int> window, int myColor)
{
	// window size is 6
	int count = 0; // The number of pieces on the four central points
	int empty = 0; // The number of empty spaces on the four central points.
	int both_ends_empty = 0;
	int one_end_empty = 0;
	int oppColor = (myColor == BLACK ? WHITE : BLACK);

	for (int i = 1; i < window.size() - 1; i++)
	{
		if (window[i] == myColor)
		{
			count++;
		}
		else if (window[i] == EMPTY)
		{
			empty++;
		}
	}

	if (window[0] == EMPTY && window[window.size() - 1] == EMPTY)
	{
		both_ends_empty = 1;
	}
	else if (window[0] == oppColor && window[window.size() - 1] == EMPTY)
	{
		one_end_empty = 1;
	}
	else if (window[0] == EMPTY && window[window.size() - 1] == oppColor)
	{
		one_end_empty = 1;
	}

	if (count == 4)
	{
		if (window[0] == myColor || window[window.size() - 1] == myColor) // ooooo_, _ooooo
		{
			return 100000;
		}
		if (both_ends_empty) // _oooo_
		{
			return 10000;
		}
		else if (one_end_empty) // xoooo_
		{
			return 1000;
		}
	}
	else if (count == 3)
	{
		if (both_ends_empty && empty == 1) // _ooo__, _o_oo_
		{
			return 500;
		}
		else if (one_end_empty && empty == 1) // xooo__, x_o_oo_
		{
			return 50;
		}
	}
	else if (count == 2)
	{
		if (both_ends_empty && empty == 2) // _oo___, _o_o__, _o__o_
		{
			return 20;
		}
		else if (one_end_empty && empty == 2) // xoo___, xo_o__, x_o_o_
		{
			return 5;
		}
	}
	return 0;
}

int AIPlayer::EvaluateLine(vector<int> line, int color)
{
	int score = 0;

	int n = line.size();
	int i = 0;

	vector<int> window;

	if (n == 5)
	{
		int isFive = 1;
		for (int i = 0; i < n; i++)
		{
			if (line[i] != color)
			{
				isFive = 0;
				break;
			}
		}
		if (isFive)
		{
			score = 100000;
			return score;
		}
	}

	for (int i = 0; i <= n - 6; i++)
	{
		window.assign(line.begin() + i, line.begin() + i + 6);
		score += ScorePattern(window, color);
	}

	return score;
}

double AIPlayer::EvaluateBoard(ChessBoard& board)
{
	double score = 0;
	int myColor = stoneColor;
	int oppColor = (stoneColor == BLACK ? WHITE : BLACK);

	// Scan 4 directions: horizontal, vertical, diag, anti-diag
	vector<int> line;

	// Horizontal
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		line.clear();
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			line.push_back(board.GetAt(BoardCoord(i, j)));
		}
		score += EvaluateLine(line, myColor);
		score -= EvaluateLine(line, oppColor) * 1.05; // slightly prefer defense
	}

	// Vertical
	for (int j = 0; j < BOARD_SIZE; j++)
	{
		line.clear();
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			line.push_back(board.GetAt(BoardCoord(i, j)));
		}
		score += EvaluateLine(line, myColor);
		score -= EvaluateLine(line, oppColor) * 1.05;
	}

	// Main diagonal (\)
	for (int d = -(BOARD_SIZE - 1); d <= BOARD_SIZE - 1; d++)
	{
		line.clear();
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			int j = i - d;
			if (j >= 0 && j < BOARD_SIZE)
				line.push_back(board.GetAt(BoardCoord(i, j)));
		}
		if (line.size() >= 5)
		{
			score += EvaluateLine(line, myColor);
			score -= EvaluateLine(line, oppColor) * 1.05;
		}
	}

	// Anti-diagonal (/)
	for (int d = 0; d <= 2 * (BOARD_SIZE - 1); d++)
	{
		line.clear();
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			int j = d - i;
			if (j >= 0 && j < BOARD_SIZE)
				line.push_back(board.GetAt(BoardCoord(i, j)));
		}
		if (line.size() >= 5)
		{
			score += EvaluateLine(line, myColor);
			score -= EvaluateLine(line, oppColor) * 1.05;
		}
	}

	return score;
}


double AIPlayer::AlphaBetaPruning(ChessBoard* board, int depth, double alpha, double beta, bool is_max)
{
	double score;

	if (depth == 0 || board->GetStepNum() == MAX_STEP_NUM)
	{
		score = EvaluateBoard(*board);
		return score;
	}

	vector<BoardCoord> moves = GenerateCandidateMoves(*board);
	BoardCoord move;

	if (is_max)
	{
		score = INT_MIN;
		for (int i = 0; i < moves.size(); i++)
		{
			move = moves[i];
			board->PlaceStone(stoneColor, move);
			score = max(score, AlphaBetaPruning(board, depth - 1, alpha, beta, false));
			board->RemoveStone();

			alpha = max(alpha, score);
			if (beta <= alpha)
			{
				break;
			}
		}
		return score;
	}
	else
	{
		score = INT_MAX;
		for (int i = 0; i < moves.size(); i++)
		{
			move = moves[i];

			int humanColor = stoneColor == BLACK ? WHITE : BLACK;
			board->PlaceStone(humanColor, move);
			score = min(score, AlphaBetaPruning(board, depth - 1, alpha, beta, true));
			board->RemoveStone();

			beta = min(beta, score);
			if (beta <= alpha)
			{
				break;
			}
		}
		return score;
	}
}

BoardCoord AIPlayer::DecideNextStep(ChessBoard& board)
{
	if (board.GetStepNum() == 0) // First move must be the center
	{
		return { 7,7 };
	}
	else
	{
		int bestScore = INT_MIN;
		BoardCoord bestMove = { -1,-1 };
		vector<BoardCoord> moves = GenerateCandidateMoves(board);

		int depth = 2;

		for (int i = 0; i < moves.size(); i++)
		{
			BoardCoord move = moves[i];
			board.PlaceStone(stoneColor, move);
			int score = AlphaBetaPruning(&board, depth - 1, INT_MIN, INT_MAX, false);
			board.RemoveStone();

			if (score > bestScore)
			{
				bestScore = score;
				bestMove = move;
			}
		}
		return bestMove;
	}
}
