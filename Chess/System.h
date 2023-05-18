#pragma once
#include "Exception.h"


enum class PieceColor {
	Black = 0,
	White = 1,
};

enum class PieceName {
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
};

//=================================================================

class Position
{
private:
	int i;
	int j;

public:
	int get_i() const;
	int get_j() const;
	void set(const int i, const int j);
	void set(const Position& pos);

	Position getRelativePosition(const int i, const int j) const;

	Position();
	Position(int i, int j);
	Position(const Position& p);

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

//=================================================================

class Square {
private:
	Position position;				// Constant position

	Piece* piece;					// Reference to Piece that stands on
	const Board* const board;		// Reference to the Board its belong. A square can never change its board

public:
	Position getPosition() const;
	Square* getRelativeSquare(const int i, const int j) const;	// Get reletive square on its board
	Piece* getPiece() const;
	const Board* getBoard() const;
	bool isEmpty() const;

	Square(const Board* b, const Position& pos);
	Square(const Board* b, Piece* p, const Position& pos);
	~Square();

	string getPieceName();
};

//=================================================================

class Board {
public:
	Square** board;

	Board();
	~Board();

	Square* getSquare(const Position& pos) const;
	Square* getSquare(const int i, const int j) const;
	Piece* getPiece(const Position& pos) const;
	bool hasPiece(const Position& pos) const;
};

//=================================================================

class Piece
{
private:

protected:
	int id;					// id for vector<Piece*> of Manager

	const Square* standOn;	// Square that piece is standing on ~ Position

	PieceColor color;
	PieceName type;

	Piece(PieceColor color, const Square* stand, int id);		// Not callable from Piece instance (protected)
	// When initialize, a piece must have a square to stand on. If it has been eaten, that stand on
	// will be nullptr.

public:
	virtual ~Piece();

	PieceName getPieceName() const;
	PieceColor getPieceColor() const;
	const Board* getBoard() const;		// Get the board it belong to
	void setEaten();
	bool isEaten() const;

	virtual void move(const Position& dest);
	
	virtual vector<Position> canGo() = 0;
};

//=================================================================

// Design Pattern - Singleton

class GameState
{
private:
	static GameState* _self;
	GameState();

public:
	GameState(const GameState& gs) = delete;	// Delete copy constructor

	static GameState* getInstance();

	Position whiteKing;
	Position blackKing;

	bool turn;
	bool isPieceChoose;


	vector<Piece*> pieces;
};


