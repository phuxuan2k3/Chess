#pragma once
#include "System.h"


enum class MoveDirection {
	Up,
	Down,
	Left,
	Right,
	UpLeft,
	UpRight,
	DownLeft,
	DownRight,
};

//===================================================
// Check Square is in Danger
//===================================================

bool isDangerousSquare(const Position& src, const Board& board, Troop color);

//===================================================
// Mics
//===================================================

// Find item in vector of Position
int hasPosition(vector<Position> list, Position item);

//===================================================
// Graphics Related
//===================================================

Position coordinateToPosition(sf::Vector2i coor);

string getSprite(PieceType pn, Troop pc);

//===================================================
// Find enemy
//===================================================

// Find if there's an enemy on a specific direction
Piece* linearSearchEnemy(const Position& src, const Board& board, Troop pieceColor, MoveDirection dir);
// Find if there's an enemy on a specific set of squares
Piece* shortSearchEnemy(const Position& src, const Board& board, Troop pieceColor, int moves[][2], int range);

// Note: we can have more than 1 enemy pieces found, but we only need to
// know whether a specific enemy piece

//===================================================
// Moves
//===================================================

// Linear Move: move that goes in a straight line, but can be blocked by other pieces.
// If blocking piece is enemy piece, you can move on it (but not go over it)
// Apply for: Rook, Bishop, Queen

vector<Position> linearMove(const Position& src, const Board& board, Troop pieceColor, MoveDirection dir);

// Short Move: has a small amount of square that can be moved on. However, these moves
// are absolute, which means blockers won't effect the general availible moves.
// Apply for: Knight, King (they both have 8 moves)

vector<Position> shortMove(const Position& src, const Board& board, Troop pieceColor, int moves[][2]);

// Pawn will have its own move

//===================================================
// Move act
//===================================================

