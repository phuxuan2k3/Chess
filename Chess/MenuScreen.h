#pragma once
#include "Screen.h"
#include "GameScreen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game);
	void run(RenderWindow& window, Screen*& screen, bool& end);
};

