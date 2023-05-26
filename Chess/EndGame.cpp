#include "EndGame.h"

EndGameType LoseByCheckmate::check(bool isCanGo, King* king, const Board& board)
{
	if (isCanGo == false and isDangerousSquare(king->getPosition(), board, king->getTroop()) == true)
	{
		return (king->getTroop() == Troop::White ? EndGameType::WhiteLose : EndGameType::BlackLose);
	}
	return EndGameType::NoEndGame;
}

EndGameType DrawByStalemate::check(bool isCanGo, King* king, const Board& board)
{
	if (isCanGo == false and isDangerousSquare(king->getPosition(), board, king->getTroop()) == false)
	{
		return EndGameType::Draw;
	}
	return EndGameType::NoEndGame;
}