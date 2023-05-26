#pragma once
#include "Header.h"

using namespace sf;

class GameBar {
private:
	static GameBar* instance;
	GameBar();
public:
	static GameBar* getInstance();
	static void deleteInstance();
	void showGameBar(RenderWindow& window);
};

