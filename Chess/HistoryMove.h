#pragma once
#include "System.h"
#include <vector>

class	 Move
{
	Piece* moverPiece;
	Piece* eatenPiece;
	Position srcPos;
	Position desPos;
public:
	Move();
	Move(Piece* mover, Piece* eaten, const Position& srcPos, const Position& desPos);
	~Move();
	void deleteMove();
	Piece* getMover();
	Piece* getEaten();
	Position getSrcPos();
	Position getDesPos();
};

class VectorMoves
{
	vector<Move> moves;
	int curState;
public:
	VectorMoves();
	VectorMoves(const int& curState, const vector<Move>& moves);
	void pushBack(Piece* mover, Piece* eaten, const Position& srcPos, const Position& desPos);
	Move getAt(const int& state);
	void setCurState(const int& state);
	int getCurState();
	void popBack();
	void deleteFrom(const int& state);
};