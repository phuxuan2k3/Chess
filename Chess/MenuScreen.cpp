#include "MenuScreen.h"
#include "SFML/Audio.hpp"

MenuScreen::MenuScreen(float windowWidthScale, float windowHeightScale, RenderGame* render, GameState* game) : Screen(windowWidthScale, windowHeightScale, render, game) {}
void MenuScreen::run(RenderWindow& window, Screen* screen) {
	SoundBuffer buffer;
	if (!buffer.loadFromFile("Audio/intro.wav"))
		return ;
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	int i = 253;

	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		RectangleShape rec(Vector2f(100,100));
		rec.setFillColor(Color::Red);
		rec.setPosition(0,0);
		Texture texture;
		string spriteName = "intro/intro_" + (i < 1000 ? "000" + to_string(i) : (i < 10000 ? "00" + to_string(i) : "0" + to_string(i)));
		texture.loadFromFile(spriteName + ".jpg");
		//texture.setSmooth(true);
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(1.0 * window.getSize().x / texture.getSize().x, 1.0 * window.getSize().y / texture.getSize().y);
		window.clear();
		window.draw(sprite);
		window.display();
		i++;
		if (i == 3504) i = 253;
	}


}
  
