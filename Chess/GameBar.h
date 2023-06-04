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
	static Sprite saveBut;
	static Sprite homeBut;
	static Sprite newGame;
	static Sprite replay;
	static Text turnText;
	static int ended;
	static Text reset;
	static void updateTurn();
	
	static void updateEnded(int i);
	static GameBar* getInstance();
	static void deleteInstance();
	void showGameBar(RenderWindow& window, bool isChecked);
	static Sprite checked;
	// State for undo, redo
	static int timeline;
	static int currentState;
	static bool isReplay;

};

