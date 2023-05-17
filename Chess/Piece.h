#pragma once
#include "Game.h"




//============== 6 Types Of Pieces =================


class Pawn : public Piece
{
public:
	bool isFirstMove = true;

	Pawn(bool color, Position pos, int id);
	~Pawn();

	PieceName getPieceName() ;
	vector<Position> canGo(const Board& board);
	void move(const int& i, const int& j);
};



class Bishop : public Piece
{
public:
	Bishop(bool color, Position pos, int id);

	PieceName getPieceName();
	vector<Position> canGo(const Board& board);
};



class Knight : public Piece
{
public:
	Knight(bool color, Position pos, int id);

	PieceName getPieceName();
	vector<Position> canGo(const Board& board);
};



class Rook : public Piece
{
public:
	bool isFirstMove = true;

	Rook(bool color, Position pos, int id);

	PieceName getPieceName();
	vector<Position> canGo(const Board& board);
	void move(const int& i, const int& j);
};



class Queen : public Piece
{
public:
	Queen(bool color, Position pos, int id);

	PieceName getPieceName();
	vector<Position> canGo(const Board& board);
};



class King : public Piece
{
public:
	bool isFirstMove = true;

	King(bool color, Position pos, int id);

	PieceName getPieceName();
	vector<Position> canGo(const Board& board);
	void move(const int& i, const int& j);
};