#include "Stone.h"

Stone::Stone()
	: stoneColor(EMPTY), stoneCoord(-1, -1)
{
	;
}

Stone::Stone(int color, BoardCoord coord)
	: stoneColor(color), stoneCoord(coord)
{
	;
}

int Stone::GetColor() const
{
	return stoneColor;
}

int Stone::GetRowIdx() const
{
	return stoneCoord.GetRowIdx();
}

int Stone::GetColumnIdx() const
{
	return stoneCoord.GetColumnIdx();
}

BoardCoord Stone::GetCoord() const
{
	return stoneCoord;
}
