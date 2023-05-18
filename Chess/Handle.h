#pragma once
#include "StaticFunc.h"

class GameHandle
{
public:
	static bool isDangerousSquare(const Square* pos, PieceColor color); // color is the color of the piece which is land in the piece
};