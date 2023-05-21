#pragma once
#include "Exception.h"


// mark = about to change

enum class Troop {
	None = -1,

	Black = 0,
	White = 1,
};

enum class PieceType {
	None = -1,

	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

// Contain information for Position
enum class PosInfo {
	Invalid = -1,	// Invalid position

	Normal = 0,		// Default
	// These moves below affect other pieces
	CastlingLeft,
	CastlingRight,
	//EnPassant ??,
};

//=================================================================

// A self made data structure for mapping on a [8][8] Board
class Position
{
private:
	PosInfo info;
	int i;
	int j;

public:
	int get_i() const;
	int get_j() const;
	void set(const int i, const int j);
	void set(const Position& pos);
	PosInfo getMoveType() const;
	void setMoveType(const PosInfo& type);

	Position getRelativePosition(const int i, const int j) const;

	Position();
	Position(int i, int j);
	Position(const Position& p);
	Position(int i, int j, PosInfo info);
	Position(const Position& p, PosInfo info);

	// Only compare the position part
	bool isPosEqual(const Position& pos) const;

	bool operator== (const Position& pos);
	Position& operator= (const Position& pos);

	bool validRelativePosition(const int& i, const int& j);
	static bool isOutOfRange_abs(const int& i, const int& j);
};

//=================================================================

// NOTE: About using pointer (Ex: Piece*)
// + Its a refernce, not value
// + Therefore, no need to delete

// Forwarding classes
class Board;
class Piece;
class Square;

//=================================================================

class Square {
private:
	Position position;				// no need for position here <edit later>

	Piece* piece;					// Reference to Piece that stands on it
	const Board* const board;		// Reference to the Board its belong. A square can never change its board

public:
	Position getPosition() const;
	Square* getRelativeSquare(const int i, const int j) const;	// Get reletive square on its board
	Piece* getPiece() const;
	void setPiece(Piece* p);
	const Board* getBoard() const;
	bool isEmpty() const;

	Square(const Board* b, const Position& pos);
	Square(const Board* b, Piece* p, const Position& pos);
	~Square();
};

//=================================================================

class Board {
public:
	Square** board;

	Board();
	// Will not delete the Pieces
	~Board();

	Square* getSquare(const Position& pos) const;
	Square* getSquare(const int i, const int j) const;
	Piece* getPiece(const Position& pos) const;
	Piece* getPiece(const int i, const int j) const;

	bool hasPiece(const Position& pos) const;
	void placePiece(Piece* piece, const int i, const int j);
	void placePiece(Piece* piece, const Position& p);
};

//=================================================================

class Piece
{
private:

protected:
	Square* standOn;						// Square that piece is standing on ~ Position
											// Will determined by place function in Board
	Troop color;
	PieceType type;

	Piece();
	Piece(Troop color);						// Not callable from Piece instance (protected)
	// When initialize, a piece must have a square to stand on. If it has been eaten, that stand on
	// will be nullptr.

public:
	virtual ~Piece();

	PieceType getPieceType() const;
	Troop getTroop() const;
	const Board* getBoard() const;			// Get the board it belong to
	void setEaten();
	bool isEaten() const;
	void setStandOn(Square* stand);
	Square* getStandOn() const;

	virtual void move(const Position& dest);
	virtual vector<Position> canGo() = 0;
};



