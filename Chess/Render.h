#pragma once
#include "Pieces.h"

#define DEFAULT_SIZE 100

enum class ThemeColor {
	Black = 0,
	White = 1,
};

enum class State {
	Selected,
	NotSelected,
	// CheckMate,
	// InCheck,
};

//===================================================
// Handle the graphics part

class RenderPiece : public WrongAbleType 
{
private:
	PieceType pieceType;
	Troop troop;

public:
	RenderPiece();
	RenderPiece(PieceType pt, Troop t);
	RenderPiece(const RenderPiece& piece);
	~RenderPiece();
	
	RenderPiece& operator = (const RenderPiece& piece);
	void set(PieceType pt, Troop t);

	// When drawing a Piece, you need to get its coordinate, width, height of its corresponding square
	void draw(sf::RenderWindow& window, const sf::Vector2f& coordinate, const float width, const float height);
};

class RenderSquare
{
public:
	float width;
	float height;
	sf::Vector2f coordinate;
	ThemeColor themeColor;
	RenderPiece piece;

	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate);
	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, float width, float height);
	~RenderSquare();
	
	// Update size
	void setSize(const float& width, const float& height);
	void setPiece(PieceType pType, Troop troop);
	void setPiece(const RenderPiece& piece);
	void setNullPiece();

	// Draw
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window);
	void drawSelected(sf::RenderWindow& window, Position pos);
};

//===================================================

class RenderBoard
{
private:
	RenderSquare** squareMat;
	const Board* board;					// Board of the game that it's associate with 

public:
	float width;
	float height;

	RenderBoard();
	~RenderBoard();

	void setBoard(const Board* board);

	// Update functions
	void setSize(const float& width, const float& height);
	void setPieces();

	// Draw
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window, vector<Position> squares);
	void drawSelected(sf::RenderWindow& window, Position pos);
};

//===================================================

class RenderGame
{
private:
	RenderBoard b;
	State state;

public:
	RenderGame();

	State getState() const;
	void setState(State state);

	// Update
	void setBoard(const Board* board);

	// Draw
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window, vector<Position> squares);

	void drawSelected(sf::RenderWindow& window, Position pos);

};

class RenderPromote
{
public:
 static sf::Vector2i relativeToChess;
 static PieceType drawPromotion();
 static void setRelaPos(sf::Vector2i pos);


};