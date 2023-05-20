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

class RenderSquare
{
public:
	float width;
	float height;
	sf::Vector2f coordinate;
	ThemeColor themeColor;
	PieceName pieceType;
	PieceColor pieceColor;

	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate);
	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, PieceName type, PieceColor pieceColor);
	RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, PieceName type, PieceColor pieceColor, float width, float height);
	~RenderSquare();
	
	// Update functions
	void setSize(const float& width, const float& height);
	void setPiece(PieceName type, PieceColor pieceColor);

	// Draw
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window);
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

	// Update
	void setBoard(const Board* board);

	// Draw
	void draw(sf::RenderWindow& window);
	void drawCanGo(sf::RenderWindow& window, vector<Position> squares);
};

