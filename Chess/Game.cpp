#include "Game.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(Troop turn) {
	this->turn = turn;

	// Will replace this placePiece setting with placing pieces
	// independently from constructor

	// Default Placing

	// Black

	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 7));
	
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::Black, 0, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::Black, 0, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::Black, 0, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Queen, Troop::Black, 0, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::Black, 0, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::Black, 0, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::Black, 0, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::Black, 0, 7));

	// White

	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 7));

	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::White, 7, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::White, 7, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::White, 7, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Queen, Troop::White, 7, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::White, 7, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::White, 7, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::White, 7, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::White, 7, 7));

	// Setup connection

	// Black Side
	setConnection(
		(King*)this->board.getPiece(0, 4),
		(Rook*)this->board.getPiece(0, 0),
		(Rook*)this->board.getPiece(0, 7));

	// White Side
	setConnection(
		(King*)this->board.getPiece(7, 4),
		(Rook*)this->board.getPiece(7, 0),
		(Rook*)this->board.getPiece(7, 7));
}

GameState::~GameState()
{
	for (Piece* p : this->pieces) {
		delete p;
	}
}

Troop GameState::getTurn() const {
	return this->turn;
}

const Board* GameState::getRefBoard() const {
	return &(this->board);
}

void GameState::switchTurn() {
	if (this->turn == Troop::Black) {
		this->turn = Troop::White;
	}
	else {
		this->turn = Troop::Black;
	}
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j) {
	Piece* piece = nullptr;
	Square* sq = this->getRefBoard()->getSquare(i, j);

	switch (pn)
	{
	case PieceType::None:
		break;
	case PieceType::Pawn:
		piece = new Pawn(pc);
		break;
	case PieceType::Knight:
		piece = new Knight(pc);
		break;
	case PieceType::Bishop:
		piece = new Bishop(pc);
		break;
	case PieceType::Rook:
		piece = new Rook(pc);
		break;
	case PieceType::Queen:
		piece = new Queen(pc);
		break;
	case PieceType::King:
		piece = new King(pc);
		break;
	default:
		break;
	}

	this->board.placePiece(piece, i, j);
	return piece;
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const Position& p) {
	return this->initPieceOnBoard(pn, pc, p.get_i(), p.get_j());
}

void GameState::setConnection(King* king, Rook* lRook, Rook* rRook) {
	king->setConnection(lRook, rRook);
	lRook->setConnection(king);
	rRook->setConnection(king);
}
