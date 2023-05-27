#include "GameBar.h"

GameBar* GameBar::instance = NULL;
Troop GameBar::turn = Troop::White;
Text GameBar::turnText;
GameBar::GameBar() {
	
};

GameBar* GameBar::getInstance() {
	if (!instance) {
		return new GameBar();
	}
	return instance;
}
void GameBar::deleteInstance() {
	if (instance) return;
	delete instance;
	instance = NULL;
}

void GameBar::updateTurn() {
	if (turn == Troop::White) {
		turn = Troop::Black;
	}
	else {
		turn = Troop::White;
	}
	cout << "con cac" << endl;
}

void GameBar::showGameBar(RenderWindow& window) {
	//BackGroup  
	Texture textureBG;
	textureBG.loadFromFile("Image/gameBar.png");
	textureBG.setSmooth(true);
	Sprite bg;
	bg.setTexture(textureBG);
	bg.setPosition(float(0.66 * window.getSize().x), 0);
	bg.setScale(float(0.35 * window.getSize().x / textureBG.getSize().x), float(1.0 * window.getSize().y / textureBG.getSize().y));
	window.draw(bg);

	//TurnText
	Font turrnFont;
	double turnSize = 0.1 * window.getSize().y;
	turrnFont.loadFromFile("Font/gameFont_01.otf");
	turnText.setFont(turrnFont);
	turnText.setString((this->turn == Troop::White? "White":"Black"));
	turnText.setCharacterSize(turnSize);
	turnText.setFillColor((this->turn == Troop::White ? Color(255, 236, 180) : Color::Black));
	turnText.setOutlineColor(sf::Color(Color(90, 61, 43)));
	turnText.setOutlineThickness(2);
	turnText.setPosition(bg.getPosition().x + 0.5 * textureBG.getSize().x * bg.getScale().x - 80, 0.15 * window.getSize().y);
	window.draw(turnText);




}