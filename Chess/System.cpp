#include "System.h"


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
		throw PositionOutOfRangeException();
	}
	this->i = i;
	this->j = j;
}

Position::Position(const Position& p) 
{
	int i = p.get_i();
	int j = p.get_j();

	if (i < 0 || j < 0 || i > 7 || j > 7) {
		throw PositionOutOfRangeException();
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

bool Position::isOutOfRange_abs(const int& i, const int& j)
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
		throw PositionOutOfRangeException();
	}
	this->i = i;
	this->j = j;
}

void Position::set(const Position& pos) {
	int i = pos.get_i();
	int j = pos.get_j();

	if (i < 0 || j < 0 || i > 7 || j > 7) {
		throw PositionOutOfRangeException();
	}
	this->i = i;
	this->j = j;
}

bool Position::validRelativePosition(const int& i, const int& j) {
	try {
		getRelativePosition(i, j);
		return true;
	}
	catch (PositionOutOfRangeException& e) {
		return false;
	}
}

Position Position::getRelativePosition(const int i, const int j) const {
	Position p(this->i + i, this->j + j);
	return p;
}

bool Position::find(vector<Position> list) {
	for (Position i : list) {
		if (i == *this) {
			return true;
		}
	}
	return false;
}

//===================================================================
// MovePosition
//===================================================================

MovePosition::MovePosition() 
{
	this->type = MoveType::Normal;
}

MovePosition::MovePosition(const Position& p) 
{
	this->type = MoveType::Normal;
	this->position = p;
}

MovePosition::MovePosition(const Position& p, MoveType t) 
{
	this->type = t;
	this->position = p;
}

MovePosition::~MovePosition() 
{
}

void MovePosition::setMoveType(const MoveType& type) {
	this->type = type;
}

MoveType MovePosition::getMoveType() const{
	return this->type;
}

void MovePosition::setPosition(const Position& p) {
	this->position = p;
}

Position MovePosition::getPosition() const {
	return this->position;
}

MovePosition& MovePosition::operator= (const MovePosition& pos) {
	this->position = pos.position;
	this->type = pos.type;
	return *this;
}

bool MovePosition::operator== (const MovePosition& pos) {
	if (this->position == pos.position &&
		this->type == pos.type)
	{
		return true;
	}
	return false;
}

//===================================================================
// Square
//===================================================================

Square::Square(const Board* const b, const Position& pos) : board(b)	// To initialize constant attribute, use pre constructor
{
	this->piece = nullptr;
}

Square::Square(const Board* const b, Piece* p, const Position& pos) : board(b)
{
	this->piece = p;
	this->position = pos;
}

Piece* Square::getPiece() const {
	return this->piece;
}

void Square::setPiece(Piece* p) {
	this->piece = p;
}

const Board* Square::getBoard() const {
	return this->board;
}

// mark
Position Square::getPosition() const {
	return this->position;
}

bool Square::isEmpty() const {
	return this->piece == nullptr;
}

// mark
Square* Square::getRelativeSquare(const int i, const int j) const {
	Position pos;
	try {
		pos = this->getPosition().getRelativePosition(i, j);
	}
	catch (PositionOutOfRangeException& e) {
		return nullptr;
	}
	Square* s = this->board->getSquare(pos);
	return s;
}

Square::~Square() {
	delete this->piece;
}

//=======================================================
// Board
//=======================================================

Board::Board() {
	this->board = new Square * [8];
	for (int i = 0; i < 8; ++i) {
		this->board[i] = new Square[8]{
			// Shadow copy Board cause there should be one instance of Board
			Square(this, nullptr, Position(i,0)),
			Square(this, nullptr, Position(i,1)),
			Square(this, nullptr, Position(i,2)),
			Square(this, nullptr, Position(i,3)),
			Square(this, nullptr, Position(i,4)),
			Square(this, nullptr, Position(i,5)),
			Square(this, nullptr, Position(i,6)),
			Square(this, nullptr, Position(i,7)),
		};
	}
}

Board::~Board() {
	for (int i = 0; i < 8; ++i) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

Square* Board::getSquare(const int i, const int j) const {
	return &(this->board[i][j]);
}

Square* Board::getSquare(const Position& pos) const {
	return &(this->board[pos.get_i()][pos.get_j()]);
}

Piece* Board::getPiece(const int i, const int j) const {
	return this->board[i][j].getPiece();
}

Piece* Board::getPiece(const Position& pos) const {
	return this->getSquare(pos)->getPiece();
}

bool Board::hasPiece(const Position& pos) const {
	return this->getSquare(pos)->isEmpty();
}

void Board::placePiece(Piece* piece, const int i, const int j) {
	if (piece == nullptr) {
		throw UninitializedException();
	}
	this->board[i][j].setPiece(piece);
}

void Board::placePiece(Piece* piece, const Position& p) {
	this->placePiece(piece, p.get_i(), p.get_j());
}

//===================================================================
// Piece
//===================================================================

Piece::Piece(PieceColor color, Square* stand)
{
	this->type = PieceName::None;
	this->color = color;
	this->standOn = stand;
}

PieceName Piece::getPieceName() const {
	return this->type;
}

PieceColor Piece::getPieceColor() const {
	return this->color;
}

void Piece::setEaten() {
	this->standOn = nullptr;
}

bool Piece::isEaten() const {
	return this->standOn == nullptr;
}

void Piece::move(const MovePosition& dest) {
	// Set this Piece standOn value to the dest on Board
	this->standOn = this->getBoard()->getSquare(dest.getPosition());

	// If that Square is occupied by a Piece
	if (this->standOn->isEmpty() == false) {
		this->standOn->getPiece()->setEaten();	// Set that Piece standOn value to nullptr;
	}
}

const Board* Piece::getBoard() const {
	if (this->standOn == nullptr) {
		throw UninitializedException();
	}
	return this->standOn->getBoard();
}

void Piece::setSquare(Square* stand) {
	this->standOn = stand;
}

Square* Piece::getSquare() const {
	return this->standOn;
}

Piece::~Piece()
{
}
