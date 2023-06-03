#pragma once
#include "Header.h"
#include "Pieces.h"

using namespace sf;

class GameBar {
private:
	static GameBar* instance;
	GameBar();
public:
	static Troop turn; 
	static Sprite undoBut;
	static Sprite redoBut;
	static Sprite homeBut;
	static Text turnText;
	static bool ended;
	static Text reset;
	static void updateTurn();
	static void updateEnded();
	static GameBar* getInstance();
	static void deleteInstance();
	void showGameBar(RenderWindow& window);

	// State for undo, redo
	static int timeline;
	static int currentState;

};

