#pragma once
#include "StaticFunc.h"


//class PieceConnection {
//private:
//	Position dest;
//
//public:
//	PieceConnection();
//
//	void setConnection(const Position& dest);
//	Position getDestPosition() const;
//};

class Castling 
{
private:
	bool castlable;

protected:
	Castling();

public:
	void unCastlable();
	bool isCastlable() const;
};

//============== 6 Types Of Pieces =================

class King;	// Forwarding this

class Pawn : public Piece
{
private:
	bool pawnFirstMove;

public:
	Pawn(Troop color);
	~Pawn();

	virtual void triggerOnFirstMove();
	vector<Position> canGo(const Position& src, const Board& board);
};



class Bishop : public Piece
{
public:
	Bishop(Troop color);

	vector<Position> canGo(const Position& src, const Board& board);
};



class Knight : public Piece
{
public:
	Knight(Troop color);

	vector<Position> canGo(const Position& src, const Board& board);
};



class Rook : public Piece, public Castling
{

public:
	Rook(Troop color);

	vector<Position> canGo(const Position& src, const Board& board);

	virtual void triggerOnFirstMove();
};



class Queen : public Piece
{
public:
	Queen(Troop color);

	vector<Position> canGo(const Position& src, const Board& board);
};



class King : public Piece, public Castling
{
private:
	Position leftRook;
	Position rightRook;

public:
	King(Troop color);

	vector<Position> canGo(const Position& src, const Board& board);

	virtual void triggerOnFirstMove();
	void setRooksPosition(const Position& lRook, const Position& rRook);	// To move Rook on castling
	Position getLeftRook() const;
	Position getRightRook() const;
};