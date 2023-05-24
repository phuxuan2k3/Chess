#pragma once
#include "Render.h"
#include "Game.h"
#include "Screen.h"
#include "GameScreen.h"

class GUI {
private:
	sf::RenderWindow window;	// Singleton this?
	float windowWidthScale;
	float windowHeightScale;
	Screen* screen;
	RenderGame* render;
	GameState* game;
	bool changeScreen;
	bool end;

public:
	GUI();
	void setScreen(int index);
	void drawGameScreen();
	void drawCanGo(const Position& selectedSquare, vector<Position> cango);

	void run();
	void run2() {
		while (true) {
			if (this->end) break;
			if (!this->changeScreen) continue;
			this->changeScreen = false;
			this->screen->run(this->window);
		}
	}

};
