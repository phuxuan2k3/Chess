#include "System.h"


Piece::Piece(bool color, Position pos, int id)
{
	this->color = color;
	this->pos = pos;
	this->id = id;

	GameState::getInstance()->pieces.push_back(this);
}

void Piece::move(const int& i, const int& j)
{
	this->pos.i = i;
	this->pos.j = j;
}

Piece::~Piece()
{
}


Position::Position()
{
	this->i = 0;
	this->j = 0;
}

Position::Position(const int& i, const int& j)
{
	this->i = i;
	this->j = j;
}

bool Position::operator== (const Position& pos)
{
	return this->i == pos.i && this->j == pos.j;
}

bool Position::isOutOfRange(const int& i, const int& j)
{
	if (i < 0 || j < 0 || i>7 || j>7)
	{
		return true;
	}
	return false;
}

//===================================================================
// Square
//===================================================================

Square::Square() {
	this->piece = nullptr;
}

Square::Square(Piece* p) {
	this->piece = p;
}

string Square::getPieceName()
{
	PieceName p = this->piece->getPieceName();

	switch (p)
	{
	case pnPawn:
		if (this->piece->color == 1)
		{
			return "pt";
		}
		return "p";
		break;

	case pnKnight:
		if (this->piece->color == 1)
		{
			return "knt";
		}
		return "kn";
		break;

	case pnBishop:
		if (this->piece->color == 1)
		{
			return "bt";
		}
		return "b";
		break;

	case pnRook:
		if (this->piece->color == 1)
		{
			return "rt";
		}
		return "r";
		break;

	case pnQueen:
		if (this->piece->color == 1)
		{
			return "qt";
		}
		return "q";
		break;

	case pnKing:
		if (this->piece->color == 1)
		{
			return "kit";
		}
		return "ki";
		break;

	default:
		break;
	}
	return "";
}

Square::~Square() {
	delete this->piece;
}


Board::Board() {
	this->board = new Square * [8];
	for (int i = 0; i < 8; ++i) {
		this->board[i] = new Square[8]{
			nullptr 
		};
	}
}


Board::~Board() {
	for (int i = 0; i < 8; ++i) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

//=======================================================
// // GameState
//=======================================================

GameState::GameState() {
	this->turn = 1;
	this->isPieceChoose = false;
}

GameState* GameState::getInstance() {
	if (_self == nullptr)
	{
		_self = new GameState();
		return _self;
	}
	else
	{
		return _self;
	}
}

// Dat o day de no co khai bao cho bien static _self sau khi da khai bao ham static getInstance()
GameState* GameState::_self = nullptr;