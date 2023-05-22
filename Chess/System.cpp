#include "System.h"



WrongAbleType::WrongAbleType() {
	this->notNull = true;
}

void WrongAbleType::setNull() {
	this->notNull = false;
}

void WrongAbleType::setNotNull() {
	this->notNull = true;
}

bool WrongAbleType::isNotNull() const {
	return this->notNull;
}

//===================================================================
// Position
//===================================================================

void Position::updateValid() {
	if (this->i < 0 ||
		this->j < 0 ||
		this->i > 7 || 
		this->j > 7) 
	{
		this->setNull();
	}
	else {
		this->setNotNull();
	}
}

Position::Position()
{
	this->i = -1;
	this->j = -1;
	this->info = PosInfo::Normal;
	this->updateValid();
}

Position::Position(int i, int j)
{
	this->i = i;
	this->j = j;
	this->info = PosInfo::Normal;
	this->updateValid();
}

Position::Position(const Position& p) 
{
	this->i = p.get_i();
	this->j = p.get_j();
	this->info = p.info;
	this->updateValid();
}

Position::Position(int i, int j, PosInfo info) 
{
	this->i = i;
	this->j = j;
	this->info = info;
	this->updateValid();
}

bool Position::operator== (const Position& pos)
{
	return this->i == pos.i 
		&& this->j == pos.j
		&& this->info == pos.info;
}

bool Position::isPosEqual(const Position& pos) const {
	return this->i == pos.i
		&& this->j == pos.j;
}

Position& Position::operator= (const Position& pos) {
	this->set(pos);
	this->info = pos.info;
	this->updateValid();
	return *this;
}

int Position::get_i() const {
	return this->i;
}

int Position::get_j() const {
	return this->j;
}

void Position::set(const int i, const int j) {
	this->i = i;
	this->j = j;
	this->updateValid();
}

void Position::set(const Position& pos) {
	this->i = pos.get_i();
	this->j = pos.get_j();
	this->updateValid();
}

PosInfo Position::getInfo() const {
	return this->info;
}

void Position::setMoveType(const PosInfo& type) {
	this->info = type;
}

Position Position::getRelativePosition(const int i, const int j) const {
	Position p(this->i + i, this->j + j);
	return p;
}

//===================================================================
// Square
//===================================================================

Square::Square() 
{
	this->piece = nullptr;
}

Square::Square(Piece* p) 
{
	this->piece = p;
}

Piece* Square::getPiece() const {
	return this->piece;
}

void Square::setPiece(Piece* p) {
	this->piece = p;
}

bool Square::isEmpty() const {
	return this->piece == nullptr;
}

Square::~Square() 
{
}

//=======================================================
// Board
//=======================================================

Board::Board() {
	this->board = new Square * [8];
	for (int i = 0; i < 8; ++i) {
		this->board[i] = new Square[8];
	}
}

Board::~Board() {
	for (int i = 0; i < 8; ++i) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

Square Board::getSquare(const int i, const int j) const {
	Position p(i, j);
	if (p.isNotNull() == false) {
		throw OutsideBoard();
	}
	return this->board[i][j];
}

Square Board::getSquare(const Position& pos) const {
	return this->board[pos.get_i()][pos.get_j()];
}

Piece* Board::getPiece(const int i, const int j) const {
	return this->board[i][j].getPiece();
}

Piece* Board::getPiece(const Position& pos) const {
	return this->getSquare(pos).getPiece();
}

bool Board::hasPiece(const Position& pos) const {
	return !this->getSquare(pos).isEmpty();
}

// PlacePiece is different than setPiece about it also set piece.standOn
// to the square that it gonna be placed on

void Board::setPiece(const int i, const int j, Piece* piece) {
	this->board[i][j].setPiece(piece);
}

void Board::setPiece(const Position& p, Piece* piece) {
	this->setPiece(p.get_i(), p.get_j(), piece);
}

//===================================================================
// Piece
//===================================================================

Piece::Piece(Troop color)
{
	// let the subclass initialize type
	this->isFirstMove = true;
	this->color = color;
}

PieceType Piece::getPieceType() const {
	return this->type;
}

Troop Piece::getTroop() const {
	return this->color;
}

Piece::~Piece()
{
}

