#pragma once
#include "Exception.h"


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
	Normal = 0,		// Default
	// These moves below affect other pieces
	CastlingLeft,
	CastlingRight,
	PawnMovedTwoStep, // Nếu con tốt đi 2 bước đầu tiên
	EnPassant, // Bắt chốt qua đường
	Promote, // Phong hậu
	RookFirstMove,
	KingFirstMove,
	PawnFirstMove,
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
};

//=================================================================

class Piece
{
private:

protected:
	bool lastChosen;
	Troop color;
	PieceType type;

	Piece();
	Piece(Troop color);
	Piece(const Piece& p);

public:
	virtual ~Piece();

	PieceType getPieceType() const;
	Troop getTroop() const;

	// Full set property (copy)
	virtual void set(const Piece* p);

	// NullPiece will always false
	virtual bool isLastChosen() const;
	virtual void setNotLastChosen();
	virtual void setLastChosen();

	// Some kinds of piece may perform differently
	virtual bool isKing() const;
	virtual bool isNullPiece() const;

	// Trigger here only can only change pieces's property
	virtual void triggerOnMoved(const Position& dest);
	// Pass troop (color) of the requestor in to determine if its enemy or ally
	virtual bool canBeEnpassant(Troop requestor);
	virtual bool canCastle(Troop requestor);

	virtual vector<Position> canGo(const Position& src, const Board& board) = 0;
	virtual Piece* deepCopyPiece(Piece* p) = 0;
};



