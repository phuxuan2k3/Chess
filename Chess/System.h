#pragma once
#include "Header.h"


enum PieceColor {
	Black,
	White,
};

enum PieceName {
	pnPawn,
	pnKnight,
	pnBishop,
	pnRook,
	pnQueen,
	pnKing,
};

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

class Piece;

class Square {
public:
	Piece* piece;

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

class Piece
{
public:
	int id; // this id is used for vector<Piece*> of Manager
	Position pos;
	bool color; //1: white,  0 black

	Piece(bool color, Position pos, int id);
	virtual ~Piece();

	virtual PieceName getPieceName() = 0;
	virtual void move(const int& i, const int& j);
	virtual vector<Position> canGo(const Board& board) = 0;
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


