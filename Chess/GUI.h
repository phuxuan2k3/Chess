#pragma once
#include "Render.h"
#include "Game.h"
#include "Screen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "GameBar.h"

class GUI {
private:
	sf::RenderWindow window;	// Singleton this?
	float windowWidthScale;
	float windowHeightScale;
	Screen* screen;
	RenderGame* render;
	GameState* game;
	bool end;

public:
	GUI();
	void run();
	~GUI();
};
