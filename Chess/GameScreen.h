#pragma once
#include "Screen.h"
#include "GameBar.h"

class GameScreen : public Screen
{
private: 
	GameBar* gameb;
public:
	GameScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game);
	void drawGameScreen(RenderWindow& window);
	void drawCanGo(RenderWindow& window,const Position& selectedSquare, vector<Position> cango);
	void run(RenderWindow& window, Screen*& screen, bool& end);

	void chessPos(RenderWindow& window);
};

