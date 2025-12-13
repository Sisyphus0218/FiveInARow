#pragma once

#include <cmath>
#include "Head.h"

class BoardNotation;

class BoardCoord
{
	// Coordinate of chessBoard[SIZE][SIZE]
private:
	int rowIdx;
	int columnIdx;

public:
	BoardCoord();
	BoardCoord(const BoardCoord& coord);
	BoardCoord(int row, int column);
	BoardCoord& operator= (const BoardCoord& coord);
	~BoardCoord() = default;

	int GetRowIdx() const;
	int GetColumnIdx() const;
	bool IsValid() const;
	int DistanceTo(BoardCoord& target) const;
	BoardNotation ToNotation() const;
};