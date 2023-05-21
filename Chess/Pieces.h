#pragma once
#include "StaticFunc.h"


// Pieces that has special first move: Pawn, King, Rook
class FirstMovePiece {
private:
	virtual void action() = 0;

protected:
	bool moved;

public:
	FirstMovePiece();
	void trigger();
};


//============== 6 Types Of Pieces =================
class King;	// Forwarding this


class Pawn : public Piece, public FirstMovePiece
{
private:
	bool isFirstMove;
	void action();

public:
	Pawn(Troop color);
	~Pawn();

	vector<Position> canGo();
	void move(const Position& dest);
};



class Bishop : public Piece
{
public:
	Bishop(Troop color);

	vector<Position> canGo();
};



class Knight : public Piece
{
public:
	Knight(Troop color);

	vector<Position> canGo();
};



class Rook : public Piece, public FirstMovePiece
{
private:
	void action();
	King* kingPiece;

public:
	Rook(Troop color);

	vector<Position> canGo();
	void move(const Position& dest);

	void setConnection(King* king);
};



class Queen : public Piece
{
public:
	Queen(Troop color);

	vector<Position> canGo();
};



class King : public Piece, public FirstMovePiece
{
private:
	void action();
	bool castlable;		// Co the nhap thanh
	Rook* leftRook;
	Rook* rightRook;

public:
	King(Troop color);

	vector<Position> canGo();
	void move(const Position& dest);

	void setConnection(Rook* lR, Rook* rR);
	void setUnCastable();
};