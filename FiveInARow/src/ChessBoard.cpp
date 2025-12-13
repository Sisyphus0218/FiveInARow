#include "ChessBoard.h"

using namespace std;

void ChessBoard::SetAt(int color, BoardCoord coord)
{
	int i = coord.GetRowIdx();
	int j = coord.GetColumnIdx();
	chessBoard[i][j] = color;
}

int ChessBoard::GetAt(BoardCoord coord)
{
	int i = coord.GetRowIdx();
	int j = coord.GetColumnIdx();
	return chessBoard[i][j];
}

void ChessBoard::PlaceStone(int color, BoardCoord coord)
{
	Stone currentStep = Stone(color, coord);
	SetAt(color, coord);
	moveHistory.push_back(currentStep);
}

void ChessBoard::RemoveStone()
{
	if (!moveHistory.empty()) {
		Stone currentStep = moveHistory.back();
		SetAt(EMPTY, currentStep.GetCoord());
		moveHistory.pop_back();
	}
	else {
		;
	}
}

Stone ChessBoard::GetCurrentStep()
{
	if (!moveHistory.empty()) {
		return moveHistory.back();
	}
	else {
		return Stone();
	}
}

int ChessBoard::GetBoardSize()
{
	return SIZE;
}

int ChessBoard::GetStepNum()
{
	return moveHistory.size();
}

int ChessBoard::IsEmptyAt(BoardCoord coord)
{
	int i = coord.GetRowIdx();
	int j = coord.GetColumnIdx();

	if (chessBoard[i][j] == EMPTY)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


