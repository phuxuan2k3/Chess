#include "MenuScreen.h"
#include "SFML/Audio.hpp"
#include <math.h>



MenuScreen::MenuScreen(float windowWidthScale, float windowHeightScale, RenderGame* render, GameState* game) : Screen(windowWidthScale, windowHeightScale, render, game) {}
void MenuScreen::run(RenderWindow& window, Screen* screen, bool& end) {
	//video
	SoundBuffer buffer;
	int i = 253;
	if (!buffer.loadFromFile("Audio/intro.wav"))
		return ;
	//sound
	Sound sound;
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();
	//text
	Font font;
	font.loadFromFile("Font/Wildheart-Regular.otf");
	

	while (window.isOpen())
	{
		sf::Event event;
	
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				end = true;
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect view(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(view));
				
			}
		}
		
		window.clear();

		// video intro
		Texture texture;
		string spriteName = "intro/intro_" + (i < 1000 ? "000" + to_string(i) : (i < 10000 ? "00" + to_string(i) : "0" + to_string(i)));
		texture.loadFromFile(spriteName + ".jpg");
		texture.setSmooth(true);
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(1.0 * window.getSize().x / texture.getSize().x, 1.0 * window.getSize().y / texture.getSize().y);
		window.draw(sprite);

		//int textSize = sqrt(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y) * 0.05;
		int textSize = window.getSize().y * 0.1;
		//Plaey Button
		Text playBut;
		playBut.setFont(font);
		playBut.setString("Play");
		playBut.setCharacterSize(textSize);
		playBut.setFillColor(sf::Color::White);
		playBut.setPosition(window.getSize().x * 0.1, window.getSize().y * 0.5);
		window.draw(playBut);
		//Plaey Button
		Text loadBut;
		loadBut.setFont(font);
		loadBut.setString("Load");
		loadBut.setCharacterSize(textSize);
		loadBut.setFillColor(sf::Color::White);
		loadBut.setPosition(window.getSize().x * 0.1, window.getSize().y * 0.5 +  textSize);
		window.draw(loadBut);
		//Plaey Button
		Text Exit;
		Exit.setFont(font);
		Exit.setString("Exit");
		Exit.setCharacterSize(textSize);
		Exit.setFillColor(sf::Color::White);
		Exit.setPosition(window.getSize().x * 0.1, window.getSize().y * 0.5 + 2 * textSize);
		window.draw(Exit);
		

		window.display();
		i++;
		if (i == 3504) i = 253;
	}


}
  

