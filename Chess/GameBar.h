#pragma once
#include "Header.h"
#include "Pieces.h"

using namespace sf;

class GameBar {
private:
	static Troop turn; 
	static GameBar* instance;
	static Sprite undoBut;
	static Text turnText;
	GameBar();
public:
	static void updateTurn();
	static GameBar* getInstance();
	static void deleteInstance();
	void showGameBar(RenderWindow& window);
};

