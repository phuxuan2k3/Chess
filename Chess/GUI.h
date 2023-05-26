#pragma once
#include "Render.h"
#include "Game.h"


class GUI {
private:
	sf::RenderWindow window;	// Singleton this?
	float windowWidthScale;
	float windowHeightScale;
	RenderGame* render;
	GameState* game;

public:
	GUI();
	void draw();
	void drawCanGo(const Position& selectedSquare, vector<Position> cango);
	void chessPos();
	void play();
};
