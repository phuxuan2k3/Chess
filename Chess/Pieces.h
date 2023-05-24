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
	bool castlable; //isFirstMove

protected:
	Castling();
	void setCastlable(bool c);
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
	Pawn(const Pawn& p);
	~Pawn();

	virtual void triggerOnFirstMove();
	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};



class Bishop : public Piece
{
public:
	Bishop(Troop color);
	Bishop(const Bishop& b);
	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};



class Knight : public Piece
{
public:
	Knight(Troop color);
	Knight(const Knight& k);
	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};



class Rook : public Piece, public Castling
{

public:
	Rook(Troop color);
	Rook(const Rook& r);
	vector<Position> canGo(const Position& src, const Board& board);

	virtual void triggerOnFirstMove();
	Piece* deepCopyPiece(Piece* p);
};



class Queen : public Piece
{
public:
	Queen(Troop color);
	Queen(const Queen& q);
	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};



class King : public Piece, public Castling
{
private:
	Position leftRook;
	Position rightRook;

public:
	King(Troop color);
	King(const King& ki);
	vector<Position> canGo(const Position& src, const Board& board);

	virtual void triggerOnFirstMove();
	void setRooksPosition(const Position& lRook, const Position& rRook);	// To move Rook on castling
	Position getLeftRook() const;
	Position getRightRook() const;
	Piece* deepCopyPiece(Piece* p);
};