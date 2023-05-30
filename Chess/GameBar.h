#pragma once
#include "Header.h"
#include "Pieces.h"

using namespace sf;

class GameBar {
private:
	static GameBar* instance;
	static Text selectedText;
	static PieceType type;
	GameBar();
public:
	static Troop turn; 
	static Sprite undoBut;
	static Sprite homeBut;
	static Text turnText;
	static int canUndo;
	static Text reset;
	static void updateTurn();
	static GameBar* getInstance();
	static void deleteInstance();
	static void updateSelected(PieceType type);
	void showGameBar(RenderWindow& window);
};

