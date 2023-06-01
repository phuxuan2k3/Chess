#include "EndGame.h"

EndGameType LoseByCheckmate::check(bool isCanGo, const Position& king, const Board& board, Troop color)
{
	if (isCanGo == false and isDangerousSquare(king, board, color) == true)
	{
		return (color == Troop::White ? EndGameType::WhiteLose : EndGameType::BlackLose);
	}
	return EndGameType::NoEndGame;
}

EndGameType DrawByStalemate::check(bool isCanGo, const Position& king, const Board& board, Troop color)
{
	if (isCanGo == false and isDangerousSquare(king, board, color) == false)
	{
		return EndGameType::Draw;
	}
	return EndGameType::NoEndGame;
}