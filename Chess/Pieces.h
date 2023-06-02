#pragma once
#include "StaticFunc.h"



class FirstMovePiece
{
private:
	bool firstMove;

public:
	FirstMovePiece();
	FirstMovePiece(const FirstMovePiece& fmp);
	void setFirstMove(bool firstMove);
	void setMoved();
	bool hasNotMove() const;
};

//============== 6 Types Of Pieces =================

class King;	// Forwarding this



class Pawn : public Piece, public FirstMovePiece
{
private:
	bool pawnFirstMoveTwoSteps;

public:
	Pawn(Troop color);
	Pawn(const Pawn& p);
	~Pawn();
	
	void set(const Piece* p);

	void triggerOnMoved(const Position& dest);
	bool canBeEnpassant(Troop requestor);

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



class Rook : public Piece, public FirstMovePiece
{
public:
	Rook(Troop color);
	Rook(Troop color, bool fromPromote);
	Rook(const Rook& r);

	void set(const Piece* p);

	void triggerOnMoved(const Position& dest);
	bool canCastle(Troop requestor);

	vector<Position> canGo(const Position& src, const Board& board);
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



class King : public Piece, public FirstMovePiece
{
private:
	Position leftRook;
	Position rightRook;

public:
	King(Troop color);
	King(const King& ki);

	void set(const Piece* p);

	void triggerOnMoved(const Position& dest);
	bool canCastle(Troop requestor);
	bool isKing() const;

	void setRooksPosition(const Position& lRook, const Position& rRook);	// To move Rook on castling
	Position getLeftRook() const;
	Position getRightRook() const;

	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};


// Null object - Singleton
// When a square has no piece on it
// Used for nullptr case of Piece, very useful, dont delete
// 
class NullPiece : public Piece 
{
private:
	static NullPiece* instance;

	NullPiece();
public:
	static NullPiece* getInstance();
	static void deleteInstance();

	void setNotLastChosen();
	void setLastChosen();
	bool isLastChosen() const;

	bool isNullPiece() const;

	vector<Position> canGo(const Position& src, const Board& board);
	Piece* deepCopyPiece(Piece* p);
};
