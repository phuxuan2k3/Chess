#pragma once
#include "Pieces.h"


class RenderSquare
{
public:
	Square* square;

	float width;
	float height;
	sf::Vector2f coordinate;
	bool color;

	RenderSquare(bool color = true);
	~RenderSquare();
	
	void setSize(const float& width, const float& height);

	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window);
};


class RenderBoard
{
public:
	RenderSquare** sqMat;
	Board Board;

	float width;
	float height;

	RenderBoard();
	~RenderBoard();

	void setSize(const float& width, const float& height);
	void draw(sf::RenderWindow& window);
};


class Manager
{
public:
	sf::RenderWindow window;
	float windowWidthScale;
	float windowHeightScale;
	RenderBoard b;

	Manager();

	Position coordinateToPosition(sf::Vector2i coor);
	void play();
};

