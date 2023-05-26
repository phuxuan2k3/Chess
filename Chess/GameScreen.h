#pragma once
#include "Screen.h"
class GameScreen : public Screen
{
public:
	GameScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game);
	void drawGameScreen(RenderWindow& window);
	void drawCanGo(RenderWindow& window,const Position& selectedSquare, vector<Position> cango);
	void run(RenderWindow& window, Screen*& screen, bool& end);

	void chessPos(RenderWindow& window);
};

