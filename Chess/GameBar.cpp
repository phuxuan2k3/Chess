#include "GameBar.h"

GameBar* GameBar::instance = NULL;

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

void GameBar::showGameBar(RenderWindow& window) {
	Texture texture;
	texture.loadFromFile("Image/gameBar.png");
	texture.setSmooth(true);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(float(0.66 * window.getSize().x), 0);
	sprite.setScale(float(0.35 * window.getSize().x / texture.getSize().x), float(1.0 * window.getSize().y / texture.getSize().y));
	std::cout << texture.getSize().x << endl;
	window.draw(sprite);
}