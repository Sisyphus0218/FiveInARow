#include "BoardCoord.h"
#include "BoardNotation.h"

BoardCoord::BoardCoord()
	:rowIdx(-1), columnIdx(-1)
{
	;
}

BoardCoord::BoardCoord(const BoardCoord& coord)
	:rowIdx(coord.GetRowIdx()), columnIdx(coord.GetColumnIdx())
{
	;
}

BoardCoord::BoardCoord(int row, int column)
	:rowIdx(row), columnIdx(column)
{
	;
}

BoardCoord& BoardCoord::operator= (const BoardCoord& coord)
{
	rowIdx = coord.GetRowIdx();
	columnIdx = coord.GetColumnIdx();
	return *this;
}

int BoardCoord::GetRowIdx() const
{
	return rowIdx;
}

int BoardCoord::GetColumnIdx() const
{
	return columnIdx;
}

bool BoardCoord::IsValid() const
{
	if (rowIdx < 0 || rowIdx > BOARD_SIZE - 1 || columnIdx < 0 || columnIdx > BOARD_SIZE - 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int BoardCoord::DistanceTo(BoardCoord& target) const
{
	if (target.IsValid() == 0)
	{
		return -1;
	}

	int otherRowIdx = target.GetRowIdx();
	int otherColumnIdx = target.GetColumnIdx();

	int isSameRow = (rowIdx == otherRowIdx);
	int isSameColumn = (columnIdx == otherColumnIdx);
	int isMainDiagonal = ((rowIdx - columnIdx) == (otherRowIdx - otherColumnIdx));
	int isAntiDiagonal = ((rowIdx + columnIdx) == (otherRowIdx + otherColumnIdx));

	if (isSameRow)
	{
		return abs(columnIdx - otherColumnIdx);
	}
	else if (isSameColumn || isMainDiagonal || isAntiDiagonal)
	{
		return abs(rowIdx - otherRowIdx);
	}
	else
	{
		return -1;
	}
}

BoardNotation BoardCoord::ToNotation() const
{
	char colChar = columnIdx + 'A';
	int rowNum = BOARD_SIZE - rowIdx;
	BoardNotation notation = BoardNotation(colChar, rowNum);
	return notation;
}
