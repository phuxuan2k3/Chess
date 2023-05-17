#pragma once
#include "System.h"

class GameHandle
{
public:
	static bool isDangerousSquare(const Board& board, Position pos, bool color); // color is the color of the piece which is land in the piece
};