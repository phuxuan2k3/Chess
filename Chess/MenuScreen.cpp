#include "MenuScreen.h"

MenuScreen::MenuScreen(float windowWidthScale, float windowHeightScale, RenderGame* render, GameState* game) : Screen(windowWidthScale, windowHeightScale, render, game) {}
void MenuScreen::run(RenderWindow& window, Screen* screen) {
	
}


//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Video Player");
//
//    sf::Video video;
//    if (!video.openFromFile("video.ogg"))  // Replace "video.ogg" with your video file path
//    {
//        // Failed to open video
//        return 1;
//    }
//
//    video.play();
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(video);
//        window.display();
//    }
//
//    return 0;
//}