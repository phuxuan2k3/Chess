#pragma once
#include "Header.h"

class Position
{
public:
	int i;
	int j;
	Position();
	Position(const int& i, const int& j);
	bool operator== (const Position& pos);
	static bool isOutOfRange(const int& i, const int& j);
};


class Square
{
public:
	float width;
	float height;
	Piece* piece;
	sf::Vector2f coordinate;
	bool color;
	Square();
	void setSize(const float& width, const float& height);
	string getPieceName();
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window);
};

class Board
{
public:
	float width;
	float height;
	Square board[8][8];
	Board();
	void setSize(const float& width, const float& height);
	void draw(sf::RenderWindow& window);
	~Board();
};

class Manager
{
public:
	sf::RenderWindow window;
	float windowWidthScale;
	float windowHeightScale;
	Board b;

	Position* whiteKing;
	Position* blackKing;

	bool turn;
	bool isPieceChoose;

	static vector<Piece*> pieces;
	static bool isDangerousSquare(Square board[8][8], Position pos, bool color); // color is the color of the piece which is land in the piece
	Position coordinateToPosition(sf::Vector2i coor);
	Manager();
	void play();
};