#pragma once
#include "Exception.h"


// mark = about to change

enum class Troop {
	Black = 0,
	White = 1,
};

enum class PieceType {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

// Contain information for Position
enum class PosInfo {
	Normal = 0,		// Default
	// These moves below affect other pieces
	CastlingLeft,
	CastlingRight,
	FirstPawnMove, // Nếu vị trí là nước đi đầu tiên của con chốt
	EnPassant // Bắt chốt qua đường
};

//=================================================================

// Classes that can have instances that do not suitable with logic.
// This is a replacement for throwing uneccessary exceptions.

class WrongAbleType {
private:
	bool notNull;

public:
	// Initialize as true
	WrongAbleType();

	bool isNotNull() const;
	void setNull();
	void setNotNull();

	virtual void updateValid() {}
};

//=================================================================

// A self made data structure for mapping on a [8][8] Board
class Position : public WrongAbleType
{
private:
	PosInfo info;
	int i;
	int j;
	virtual void updateValid();

public:
	int get_i() const;
	int get_j() const;
	void set(const int i, const int j);
	void set(const Position& pos);
	PosInfo getInfo() const;
	void setMoveType(const PosInfo& type);

	Position getRelativePosition(const int i, const int j) const;

	Position();	// Uninitialized Position is invalid
	Position(int i, int j);
	Position(const Position& p);
	Position(int i, int j, PosInfo info);

	// Only compare the position part
	bool isPosEqual(const Position& pos) const;

	bool operator== (const Position& pos);
	Position& operator= (const Position& pos);
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
	Piece* piece;				// Reference to Piece that stands on it

public:
	Piece* getPiece() const;
	void setPiece(Piece* p);
	bool isEmpty() const;

	Square();
	Square(Piece* p);
	~Square();
};

//=================================================================

class Board {
public:
	Square** board;

	Board();
	// Will not delete the Pieces
	~Board();

	Square getSquare(const Position& pos) const;
	Square getSquare(const int i, const int j) const;
	Piece* getPiece(const Position& pos) const;
	Piece* getPiece(const int i, const int j) const;
	void setPiece(const int i, const int j, Piece* piece);
	void setPiece(const Position& p, Piece* piece);

	bool hasPiece(const Position& pos) const;

	static bool EnPassantBlack; // Quân đen bắt tốt được
	static bool EnPassantWhite; // quân trắng bắt tốt được 
	static Piece* lastChoose; // con cờ được chọn cuối
};

//=================================================================

class Piece : public WrongAbleType
{
private:

protected:
	bool isFirstMove;
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

	// Do nothing on normal pieces: Knight, Bishop, Queen
	virtual void triggerOnFirstMove() {}
	virtual vector<Position> canGo(const Position& src, const Board& board) = 0;
};



