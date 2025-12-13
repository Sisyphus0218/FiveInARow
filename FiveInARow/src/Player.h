#pragma once

#include "BoardCoord.h"
#include "ChessBoard.h"
#include "Head.h"

class Player
{
protected:
	int stoneColor;

public:
	Player();
	Player(int color);
	virtual ~Player();

	virtual BoardCoord DecideNextStep(ChessBoard& board) = 0;
};

