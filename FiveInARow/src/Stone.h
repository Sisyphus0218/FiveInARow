#pragma once

#include "BoardCoord.h"
#include "Head.h"

class Stone
{
private:
	int stoneColor;
	BoardCoord stoneCoord;

public:
	Stone();
	Stone(int color, BoardCoord coord);
	~Stone() = default;

	int GetColor() const;
	int GetRowIdx() const;
	int GetColumnIdx() const;
	BoardCoord GetCoord() const;
};

