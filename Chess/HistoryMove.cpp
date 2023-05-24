#include "HistoryMove.h"
#include "Pieces.h"

Move::Move()
{
	this->moverPiece = nullptr;
	this->eatenPiece = nullptr;
}

Move::Move(Piece* mover, Piece* eaten, const Position& srcPos, const Position& desPos)
{
	this->moverPiece = mover;
	this->eatenPiece = eaten;
	this->srcPos = srcPos;
	this->desPos = desPos;
}

Move::~Move()
{
}

void Move::deleteMove()
{
	delete this->moverPiece;
	delete this->eatenPiece;
}

Piece* Move::getCopyMover()
{
	return this->moverPiece->deepCopyPiece(this->moverPiece);
}

Piece* Move::getCopyEaten()
{
	if (this->eatenPiece)
	{
		return this->eatenPiece->deepCopyPiece(this->eatenPiece);
	}
	return nullptr;
}

Piece* Move::getMover()
{
	return this->moverPiece;
}

Piece* Move::getEaten()
{
	return this->eatenPiece;
}

Position Move::getSrcPos()
{
	return this->srcPos;
}

Position Move::getDesPos()
{
	return this->desPos;
}

VectorMoves::VectorMoves()
{
	this->curState = -1;
}

VectorMoves::VectorMoves(const int& curState, const vector<Move>& moves)
{
	this->curState = curState;
	this->moves = moves;
}

void VectorMoves::pushBack(Piece* mover, Piece* eaten, const Position& srcPos, const Position& desPos)
{
	this->moves.push_back(Move(mover, eaten, srcPos, desPos));
	this->curState++;
}

Move VectorMoves::getAt(const int& state)
{
	if (state > this->moves.size() - 1)
	{
		return this->moves.at(this->moves.size() - 1);
	}
	return this->moves.at(state);
}

void VectorMoves::setCurState(const int& state)
{
	this->curState = state;
}

int VectorMoves::getCurState()
{
	return this->curState;
}

void VectorMoves::popBack()
{
	if (this->moves.empty() == false)
	{
		Move m = this->moves.at(this->moves.size() - 1);
		m.deleteMove();
		this->moves.pop_back();
	}
}

void VectorMoves::deleteFrom(const int& state)
{
	while (this->moves.size() - 1 >= state && this->moves.empty() == false)
	{
		this->popBack();
	}
}