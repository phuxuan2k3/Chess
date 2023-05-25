#include "GUI.h"


//===================================================
// GUI
//===================================================



GUI::GUI() {
	this->window.create(sf::VideoMode(950, 800), "");
	this->windowHeightScale = 1;
	this->windowWidthScale = 1;
	this->render = new RenderGame();
	this->game = new GameState();
	this->end = false;
	// Connect board
	this->render->setBoard(this->game->getRefBoard());
	this->screen = new MenuScreen(this->windowWidthScale,this->windowWidthScale,this->render,this->game);
}

// Change state to NotSelected
void GUI::drawGameScreen() {
	this->window.clear();
	this->render->draw(this->window);
	this->window.display();
}

// Change state to Selected
void GUI::drawCanGo(const Position& selectedSquare, vector<Position> cango) {

	this->window.clear();
	this->render->draw(this->window);
	this->render->drawCanGo(this->window, cango);
	this->window.display();
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
}