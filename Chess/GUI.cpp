#include "GUI.h"
//===================================================
// GUI
//===================================================
//===================================================
// GUI
//===================================================

GUI::GUI() {
	sf::Image icon;
	icon.loadFromFile("Image/king.jpg");
	this->window.create(sf::VideoMode(1200, 800), "Chess", sf::Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y,icon.getPixelsPtr());
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
	if(this->render) delete this->render;
	if(this->screen) delete this->screen;
}