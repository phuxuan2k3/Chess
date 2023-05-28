#include "GUI.h"
//===================================================
// GUI
//===================================================
//===================================================
// GUI
//===================================================

GUI::GUI() {
	this->window.create(sf::VideoMode(1200, 800), "Chess", sf::Style::Close);
	this->windowHeightScale = 1;
	this->windowWidthScale = 1;
	this->render = new RenderGame();
	this->game = new GameState();
	this->end = false;
	// Connect board
	this->render->setBoard(this->game->getRefBoard());
	this->screen = new MenuScreen(this->windowWidthScale, this->windowWidthScale, this->render, this->game);
}

void GUI::run()
{
	while (true) {
		if (this->end) break;
		this->screen->run(this->window, this->screen, this->end);
	}
}

GUI::~GUI() {
	delete this->screen;
	delete this->render;
	delete this->game;
}