#pragma once

#include <string>
#include "BoardCoord.h"
#include "ChessBoard.h"
#include "Head.h"
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer();
	HumanPlayer(int color);
	~HumanPlayer() = default;

	BoardCoord DecideNextStep(ChessBoard& board);
};

