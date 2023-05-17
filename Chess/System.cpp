#include "System.h"



PieceColor operator ! (const PieceColor& pc) {
	if (pc == PieceColor::Black) {
		return PieceColor::White;
	}
	else {
		return PieceColor::Black;
	}
}

//===================================================================
// Position
//===================================================================

Position::Position()
{
	this->i = 0;
	this->j = 0;
}

Position::Position(int i, int j)
{
	if (i < 0 || j < 0 || i > 7 || j > 7) {
		throw PositionException();
	}
	this->i = i;
	this->j = j;
}

bool Position::operator== (const Position& pos)
{
	return this->i == pos.i && this->j == pos.j;
}

Position& Position::operator= (const Position& pos) {
	this->set(pos);
	return *this;
}

bool Position::isOutOfRange(const int& i, const int& j)
{
	if (i < 0 || j < 0 || i > 7 || j > 7) {
		return true;
	}
	return false;
}

int Position::get_i() const {
	return this->i;
}

int Position::get_j() const {
	return this->j;
}

void Position::set(const int i, const int j) {
	if (i < 0 || j < 0 || i > 7 || j > 7) {
		throw PositionException();
	}
	this->i = i;
	this->j = j;
}

void Position::set(const Position& pos) {
	int i = pos.get_i();
	int j = pos.get_j();
	if (i < 0 || j < 0 || i > 7 || j > 7) {
		throw PositionException();
	}
	this->i = i;
	this->j = j;
}


//===================================================================
// Piece
//===================================================================

Piece::Piece(PieceColor color, Position pos, int id)
{
	this->color = color;
	this->pos = pos;
	this->id = id;

	GameState::getInstance()->pieces.push_back(this);
}

PieceName Piece::getPieceName() const {
	return this->type;
}

PieceColor Piece::getPieceColor() const {
	return this->color;
}

void Piece::move(const Position& pos) {
	this->pos.set(pos);
}

Piece::~Piece()
{
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

Piece* Square::getPiece() const {
	return this->piece;
}

bool Square::isEmpty() const {
	return this->piece == nullptr;
}

string Square::getPieceName()
{
	PieceName p = this->piece->getPieceName();

	switch (p)
	{
	case PieceName::Pawn:
		if (this->piece->getPieceColor() == PieceColor::White)
		{
			return "pt";
		}
		return "p";
		break;
	case PieceName::Knight:
		if (this->piece->getPieceColor() == PieceColor::White)
		{
			return "knt";
		}
		return "kn";
		break;
	case PieceName::Bishop:
		if (this->piece->getPieceColor() == PieceColor::White)
		{
			return "bt";
		}
		return "b";
		break;
	case PieceName::Rook:
		if (this->piece->getPieceColor() == PieceColor::White)
		{
			return "rt";
		}
		return "r";
		break;
	case PieceName::Queen:
		if (this->piece->getPieceColor() == PieceColor::White)
		{
			return "qt";
		}
		return "q";
		break;
	case PieceName::King:
		if (this->piece->getPieceColor() == PieceColor::White)
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