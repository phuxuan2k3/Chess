#include "MenuScreen.h"
#include "SFML/Audio.hpp"
#include <math.h>



MenuScreen::MenuScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game) : Screen(windowWidthScale, windowHeightScale, render, game) {}
void MenuScreen::run(RenderWindow& window, Screen*& screen, bool& end) {
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

	SoundBuffer hoverB;
	hoverB.loadFromFile("Audio/clickMenu.wav");
	Sound hover;
	hover.setLoop(false);
	hover.setBuffer(hoverB);
	hover.setVolume(50);
	bool choosing = false;

	//text
	Font font;
	font.loadFromFile("Font/Wildheart-Regular.otf");
	Color defaultColor = Color::White;
	Color hoverColor = Color::Green;

	//int textSize = sqrt(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y) * 0.05;
	int textSize = window.getSize().y * 0.08;
	int x = window.getSize().x * 0.08;
	int y = window.getSize().y * 0.5;
	//Chess
	Text Chess;
	Chess.setFont(font);
	Chess.setString("Chess");
	Chess.setCharacterSize(textSize * 2);
	Chess.setFillColor(sf::Color::White);
	Chess.setPosition(x, y * 0.2);
	//Play Button
	Text playBut;
	playBut.setFont(font);
	playBut.setString("Play");
	playBut.setCharacterSize(textSize);
	playBut.setFillColor(sf::Color::White);
	playBut.setPosition(x, y );

	//Load Button
	Text loadBut;
	loadBut.setFont(font);
	loadBut.setString("Load");
	loadBut.setCharacterSize(textSize);
	loadBut.setFillColor(sf::Color::White);
	loadBut.setPosition(x, y + textSize);
	//Exit Button
	Text Exit;
	Exit.setFont(font);
	Exit.setString("Exit");
	Exit.setCharacterSize(textSize);
	Exit.setFillColor(sf::Color::White);
	Exit.setPosition(x, y +  2*  textSize);

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
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				if (playBut.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
				{
					playBut.setFillColor(hoverColor);
					Exit.setFillColor(defaultColor);
					loadBut.setFillColor(defaultColor);
					if (!choosing) {
						choosing = true;
						hover.play();
					}
				}

				else if (Exit.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
				{
					Exit.setFillColor(hoverColor);
					playBut.setFillColor(defaultColor);
					loadBut.setFillColor(defaultColor);
					if (!choosing) {
						choosing = true;
						hover.play();
					}
				}
				else if (loadBut.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
					loadBut.setFillColor(hoverColor);
					Exit.setFillColor(defaultColor);
					playBut.setFillColor(defaultColor);
					if (!choosing) {
						choosing = true;
						hover.play();
					}
				}
				else
				{
					loadBut.setFillColor(defaultColor);
					playBut.setFillColor(defaultColor);
					Exit.setFillColor(defaultColor);
					choosing = false;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				if (playBut.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
				{
					Screen* temp = screen;
					screen = new GameScreen(this->windowWidthScale,this->windowHeightScale,this->render,this->game);
					delete temp;
					break;
				}
				if (Exit.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
				{	
					end = true;
					delete game;
					break;
				}
				if (loadBut.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
				{
					cout << "load game here!" << endl;
					break;
				}
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
		window.draw(playBut);
		window.draw(loadBut);
		window.draw(Exit);
		window.draw(Chess);
		window.display();
		i++;
		if (i == 3504) i = 253;
	}


}
  

