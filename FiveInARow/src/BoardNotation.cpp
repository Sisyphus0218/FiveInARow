#include "BoardCoord.h"
#include "BoardNotation.h"

BoardNotation::BoardNotation()
	:colChar(' '), rowNum(-1)
{
	;
}

BoardNotation::BoardNotation(char letter, int number)
	:colChar(letter), rowNum(number)
{
	;
}

char BoardNotation::GetColChar() const
{
	return colChar;
}

int BoardNotation::GetRowNum() const
{
	return rowNum;
}

bool BoardNotation::IsValid() const
{
	if (colChar < 'A' || colChar > 'A' + BOARD_SIZE - 1 || rowNum < 1 || rowNum > BOARD_SIZE)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

BoardCoord BoardNotation::ToCoord() const
{
	int rowIdx = BOARD_SIZE - rowNum;
	int columnIdx = colChar - 'A';
	BoardCoord coord = BoardCoord(rowIdx, columnIdx);
	return coord;
}