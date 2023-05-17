#pragma once
#include "Handle.h"


//============== 6 Types Of Pieces =================


class Pawn : public Piece
{
private:

public:
	bool isFirstMove = true;

	Pawn(PieceColor color, Position pos, int id);
	~Pawn();

	vector<Position> canGo(const Board& board);
	void move(const Position& pos);
};



class Bishop : public Piece
{
public:
	Bishop(PieceColor color, Position pos, int id);

	vector<Position> canGo(const Board& board);
};



class Knight : public Piece
{
public:
	Knight(PieceColor color, Position pos, int id);

	vector<Position> canGo(const Board& board);
};



class Rook : public Piece
{
public:
	bool isFirstMove = true;

	Rook(PieceColor color, Position pos, int id);

	vector<Position> canGo(const Board& board);
	void move(const Position& pos);
};



class Queen : public Piece
{
public:
	Queen(PieceColor color, Position pos, int id);

	vector<Position> canGo(const Board& board);
};



class King : public Piece
{
public:
	bool isFirstMove = true;

	King(PieceColor color, Position pos, int id);

	vector<Position> canGo(const Board& board);
	void move(const Position& pos);
};