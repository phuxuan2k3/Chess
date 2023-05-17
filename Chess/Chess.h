#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;



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

class Square;

class Piece
{
public:
	int id; // this id is used for vector<Piece*> of Manager
	Position pos;
	bool color; //1: white,  0 black
	Piece();
	Piece(bool color, Position pos, int id);
	virtual void move(const int& i, const int& j);
	virtual vector<Position> canGo(Square board[8][8]) = 0;
	virtual ~Piece();
};

class Pawn : public Piece
{
public:
	bool isFirstMove = true;
	Pawn(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
	void move(const int& i, const int& j);
	~Pawn();
};

class Bishop :public Piece
{
public:
	Bishop(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
};

class Knight : public Piece
{
public:
	Knight(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
};

class Rook : public Piece
{
public:
	bool isFirstMove = true;
	Rook(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
	void move(const int& i, const int& j);
};

class Queen : public Piece
{
public:
	Queen(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
};

class King :public Piece
{
public:
	bool isFirstMove = true;
	King(bool color, Position pos, int id);
	vector<Position> canGo(Square board[8][8]);
	void move(const int& i, const int& j);
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