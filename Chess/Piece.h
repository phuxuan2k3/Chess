#pragma once
#include "Header.h"


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