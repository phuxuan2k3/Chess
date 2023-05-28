#pragma once
#include "Render.h"
#include "Game.h"

using namespace sf;

class Screen
{
protected:
	float windowWidthScale;
	float windowHeightScale;
	RenderGame* render;
	GameState* game;
public:
	Screen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game);
	virtual void run(RenderWindow& window, Screen*& screen,bool& end) = 0;
	virtual ~Screen() {};
};


