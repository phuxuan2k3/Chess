#pragma once
#include "Pieces.h"

#define DEFAULT_SIZE 100

enum class ThemeColor {
	Black = 0,
	White = 1,
};

//===================================================

class RenderSquare
{
public:
	Square* square;		// Reference to the square, no delete

	float width;
	float height;
	sf::Vector2f coordinate;
	ThemeColor themeColor;

	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, Square* associate);
	~RenderSquare();
	
	void setSize(const float& width, const float& height);

	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window);
};

//===================================================

class RenderBoard
{
public:
	RenderSquare** squareMat;
	const Board* board;			// Board of the game that it's associate with 
								// (could make this Board static)

	float width;
	float height;

	RenderBoard(const Board* associate);
	~RenderBoard();

	void setSize(const float& width, const float& height);
	void draw(sf::RenderWindow& window);
};

//===================================================

class Manager
{
public:
	sf::RenderWindow window;
	float windowWidthScale;
	float windowHeightScale;
	RenderBoard b;

	Manager(const Board* broad);

	Position coordinateToPosition(sf::Vector2i coor);
	void play();
};

