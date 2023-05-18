#pragma once
#include "Handle.h"


//============== 6 Types Of Pieces =================


class Pawn : public Piece
{
private:

public:
	bool isFirstMove = true;

	Pawn(PieceColor color, const Square* stand, int id);
	~Pawn();

	vector<Position> canGo();
	void move(const Position& dest);
};



class Bishop : public Piece
{
public:
	Bishop(PieceColor color, const Square* stand, int id);

	vector<Position> canGo();
};



class Knight : public Piece
{
public:
	Knight(PieceColor color, const Square* stand, int id);

	vector<Position> canGo();
};



class Rook : public Piece
{
public:
	bool isFirstMove = true;

	Rook(PieceColor color, const Square* stand, int id);

	vector<Position> canGo();
	void move(const Position& dest);
};



class Queen : public Piece
{
public:
	Queen(PieceColor color, const Square* stand, int id);

	vector<Position> canGo();
};



class King : public Piece
{
public:
	bool isFirstMove = true;

	King(PieceColor color, const Square* stand, int id);

	vector<Position> canGo();
	void move(const Position& dest);
};