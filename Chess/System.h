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

	Position();
	Position(int i, int j);

	bool operator== (const Position& pos);
	Position& operator= (const Position& pos);

	static bool isOutOfRange(const int& i, const int& j);
};

//=================================================================

class Piece
{
private:

protected:
	int id;			// this id is used for vector<Piece*> of Manager

	Position pos;
	PieceColor color;
	PieceName type;
	
	Piece(PieceColor color, Position pos, int id);	// Not callable from Piece instance

public:
	virtual ~Piece();

	PieceName getPieceName() const;
	PieceColor getPieceColor() const;
	virtual void move(const Position& pos);
	virtual vector<Position> canGo(const Board& board) = 0;
};


class Square {
private:
	Piece* piece;

public:
	Piece* getPiece() const;
	bool isEmpty() const;

	Square();
	Square(Piece* p);
	~Square();

	string getPieceName();
};

class Board {
public:
	Square** board;

	Board();
	~Board();
};


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


