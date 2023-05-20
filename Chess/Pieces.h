#pragma once
#include "StaticFunc.h"


// Pieces that has special first move
class FirstMovePiece {
protected:
	bool moved;

public:
	FirstMovePiece();

	bool hasNotMoved() const;
	void setMoved();
};

//============== 6 Types Of Pieces =================


class Pawn : public Piece, public FirstMovePiece
{
public:
	Pawn(PieceColor color, Square* stand);
	~Pawn();

	vector<MovePosition> canGo();
	void move(const MovePosition& dest);
};



class Bishop : public Piece
{
public:
	Bishop(PieceColor color, Square* stand);

	vector<MovePosition> canGo();
};



class Knight : public Piece
{
public:
	Knight(PieceColor color, Square* stand);

	vector<MovePosition> canGo();
};



class Rook : public Piece, public FirstMovePiece
{
public:
	Rook(PieceColor color, Square* stand);

	vector<MovePosition> canGo();
	void move(const MovePosition& dest);
};



class Queen : public Piece
{
public:
	Queen(PieceColor color, Square* stand);

	vector<MovePosition> canGo();
};



class King : public Piece, public FirstMovePiece
{
private:
	Piece* leftRook;
	Piece* rightRook;

public:
	King(PieceColor color, Square* stand);

	vector<MovePosition> canGo();
	void move(const MovePosition& dest);
};