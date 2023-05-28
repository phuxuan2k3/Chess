#pragma once
#include "Header.h"
#include "Pieces.h"

using namespace sf;

class GameBar {
private:
	static Troop turn; 
	static GameBar* instance;
	static Text turnText;
	static Text selectedText;

	static PieceType type;
	GameBar();
public:	

	static void updateTurn();
	static GameBar* getInstance();
	static void deleteInstance();
	static void updateSelected(PieceType type);
	void showGameBar(RenderWindow& window);
};

