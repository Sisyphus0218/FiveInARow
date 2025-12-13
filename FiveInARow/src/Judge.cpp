#include "Judge.h"

using namespace std;

int Judge::ChessPattern(vector<int> window, int myColor)
{
	int count = 0;
	int empty = 0;
	int both_side_open = 0;
	int one_side_open = 0;
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
		both_side_open = 1;
	}
	else if (window[0] == oppColor && window[window.size() - 1] == EMPTY)
	{
		one_side_open = 1;
	}
	else if (window[0] == EMPTY && window[window.size() - 1] == oppColor)
	{
		one_side_open = 1;
	}

	if (count == 4)
	{
		if (both_side_open || one_side_open) // _oooo_
		{
			return 4;
		}
	}
	else if (count == 3)
	{
		if (both_side_open && empty == 1) // _ooo__, _o_oo_
		{
			return 3;
		}
	}
	return 0;
}

int Judge::IsLiveThree(std::vector<int> line, int color)
{
	int n = line.size();
	int i = 0;

	vector<int> window;

	for (int i = 0; i <= n - 6; i++)
	{
		window.assign(line.begin() + i, line.begin() + i + 6);
		if (ChessPattern(window, color) == 3)
		{
			return 1;
		}
	}
	return 0;
}

int Judge::IsFour(std::vector<int> line, int color)
{
	int n = line.size();
	int i = 0;

	vector<int> window;

	for (int i = 0; i <= n - 6; i++)
	{
		window.assign(line.begin() + i, line.begin() + i + 6);
		if (ChessPattern(window, color) == 4)
		{
			return 1;
		}
	}
	return 0;
}

int Judge::IsFive(std::vector<int> line, int color)
{
	int n = line.size();
	int i = 0;

	while (i < n)
	{
		if (line[i] != color) {
			i++;
			continue;
		}

		// count continuous stones
		int count = 0;
		while (i < n && line[i] == color) {
			count++;
			i++;
		}

		if (count == 5)
		{
			return 1;
		}
	}

	return 0;
}

int Judge::IsOverline(std::vector<int> line, int color)
{
	int n = line.size();
	int i = 0;
	while (i < n)
	{
		if (line[i] != color) {
			i++;
			continue;
		}
		int count = 0;
		while (i < n && line[i] == color) {
			count++;
			i++;
		}
		if (count > 5)  // 超过5个连续
		{
			return 1;
		}
	}
	return 0;
}

int Judge::CheckDoubleThreeForbidden(ChessBoard board, int color, Stone currentStep)
{
	int rowIdx = currentStep.GetRowIdx();
	int columnIdx = currentStep.GetColumnIdx();
	int boardSize = board.GetBoardSize();

	int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

	int liveThreeCount = 0;

	for (int d = 0; d < 4; d++)
	{
		int dx = directions[d][0];
		int dy = directions[d][1];

		vector<int> line;
		for (int k = -4; k <= 4; k++)
		{
			int r = rowIdx + k * dx;
			int c = columnIdx + k * dy;
			BoardCoord coord(r, c);
			if (coord.IsValid())
			{
				line.push_back(board.GetAt(BoardCoord(r, c)));
			}
		}
		if (IsLiveThree(line, color))
		{
			liveThreeCount++;
		}
	}

	if (liveThreeCount >= 2)
	{
		return 1;
	}

	return 0;
}

int Judge::CheckDoubleFourForbidden(ChessBoard board, int color, Stone currentStep)
{
	int rowIdx = currentStep.GetRowIdx();
	int columnIdx = currentStep.GetColumnIdx();
	int boardSize = board.GetBoardSize();

	int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

	int FourCount = 0;

	for (int d = 0; d < 4; d++)
	{
		int dx = directions[d][0];
		int dy = directions[d][1];

		vector<int> line;
		for (int k = -4; k <= 4; k++)
		{
			int r = rowIdx + k * dx;
			int c = columnIdx + k * dy;
			BoardCoord coord(r, c);
			if (coord.IsValid())
			{
				line.push_back(board.GetAt(BoardCoord(r, c)));
			}
		}
		if (IsFour(line, color))
		{
			FourCount++;
		}
	}

	if (FourCount >= 2)
	{
		return 1;
	}

	return 0;
}

int Judge::CheckFive(ChessBoard board, int color, Stone currentStep)
{
	int rowIdx = currentStep.GetRowIdx();
	int columnIdx = currentStep.GetColumnIdx();
	int boardSize = board.GetBoardSize();

	int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

	for (int d = 0; d < 4; d++)
	{
		int dx = directions[d][0];
		int dy = directions[d][1];

		vector<int> line;
		for (int k = -4; k <= 4; k++)
		{
			int r = rowIdx + k * dx;
			int c = columnIdx + k * dy;
			BoardCoord coord(r, c);
			if (coord.IsValid())
			{
				line.push_back(board.GetAt(BoardCoord(r, c)));
			}
		}
		if (IsFive(line, color))
		{
			return 1;
		}
	}
	return 0;
}

int Judge::CheckOverlineForbidden(ChessBoard board, int color, Stone currentStep)
{
	int rowIdx = currentStep.GetRowIdx();
	int columnIdx = currentStep.GetColumnIdx();
	int boardSize = board.GetBoardSize();

	int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };

	for (int d = 0; d < 4; d++)
	{
		int dx = directions[d][0];
		int dy = directions[d][1];

		vector<int> line;
		for (int k = -5; k <= 5; k++)
		{
			int r = rowIdx + k * dx;
			int c = columnIdx + k * dy;
			BoardCoord coord(r, c);
			if (coord.IsValid())
			{
				line.push_back(board.GetAt(BoardCoord(r, c)));
			}
		}
		if (IsOverline(line, color))
		{
			return 1;
		}
	}
	return 0;
}

int Judge::JudgeForbidden(ChessBoard board, int color, Stone currentStep)
{
	if (CheckDoubleThreeForbidden(board, color, currentStep))
	{
		return FORBIDDEN_DOUBLE_THREE;
	}
	if (CheckDoubleFourForbidden(board, color, currentStep))
	{
		return FORBIDDEN_DOUBLE_FOUR;
	}
	if (CheckOverlineForbidden(board, color, currentStep))
	{
		return FORBIDDEN_OVERLINE;
	}
	return NO_FORBIDDEN;
}

int Judge::JudgeBoard(ChessBoard board)
{
	Stone currentStep = board.GetCurrentStep();
	int color = currentStep.GetColor();
	if (CheckFive(board, color, currentStep))
	{
		return WIN;
	}
	else if (color == BLACK)
	{
		return JudgeForbidden(board, color, currentStep);
	}
	else
	{
		return NO_FORBIDDEN;
	}
}
