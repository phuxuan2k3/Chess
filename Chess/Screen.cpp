#include "Screen.h"

Screen::Screen( float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game) {
	this->windowHeightScale = windowHeightScale;
	this->windowWidthScale = windowWidthScale;
	this->render = render;
	this->game = game;
}
