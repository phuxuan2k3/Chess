#pragma once
#include "System.h"
#include "Pieces.h"
#include "StaticFunc.h"

enum class EndGameType
{
	WhiteLose,
	BlackLose,
	Draw,
	NoEndGame
};

class IEndGame
{
public:
	//this function has no sense
	virtual EndGameType check(bool isCanGo, const Position& king, const Board& board, Troop color)
	{
		return EndGameType::NoEndGame;
	}
};

class LoseByCheckmate : public IEndGame
{
public:
	EndGameType check(bool isCanGo, const Position& king, const Board& board, Troop color);
};

class DrawByStalemate : public IEndGame
{
public:
	EndGameType check(bool isCanGo, const Position& king, const Board& board, Troop color);
};