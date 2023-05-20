#include "Game.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(PieceColor turn) {
	this->turn = turn;


	// Will replace this placePiece setting with placing pieces
	// independently from constructor

	// Default Placing

	// Black

	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 0);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 1);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 2);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 3);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 4);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 5);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 6);
	this->placePiece(PieceName::Pawn, PieceColor::Black, 1, 7);
	
	this->placePiece(PieceName::Rook, PieceColor::Black, 0, 0);
	this->placePiece(PieceName::Knight, PieceColor::Black, 0, 1);
	this->placePiece(PieceName::Bishop, PieceColor::Black, 0, 2);
	this->placePiece(PieceName::Queen, PieceColor::Black, 0, 3);
	this->placePiece(PieceName::King, PieceColor::Black, 0, 4);
	this->placePiece(PieceName::Bishop, PieceColor::Black, 0, 5);
	this->placePiece(PieceName::Knight, PieceColor::Black, 0, 6);
	this->placePiece(PieceName::Rook, PieceColor::Black, 0, 7);

	// White

	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 0);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 1);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 2);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 3);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 4);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 5);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 6);
	this->placePiece(PieceName::Pawn, PieceColor::White, 6, 7);

	this->placePiece(PieceName::Rook, PieceColor::White, 7, 0);
	this->placePiece(PieceName::Knight, PieceColor::White, 7, 1);
	this->placePiece(PieceName::Bishop, PieceColor::White, 7, 2);
	this->placePiece(PieceName::Queen, PieceColor::White, 7, 3);
	this->placePiece(PieceName::King, PieceColor::White, 7, 4);
	this->placePiece(PieceName::Bishop, PieceColor::White, 7, 5);
	this->placePiece(PieceName::Knight, PieceColor::White, 7, 6);
	this->placePiece(PieceName::Rook, PieceColor::White, 7, 7);


	// Arkward setting (need to be fixed)
	// Black King set Rook
	((King*)this->board.getPiece(0, 4))->setRook(
		this->board.getPiece(0, 0),
		this->board.getPiece(0, 7));
	// White King set Rook
	((King*)this->board.getPiece(7, 4))->setRook(
		this->board.getPiece(7, 0),
		this->board.getPiece(7, 7));
}

GameState::~GameState()
{
}

PieceColor GameState::getTurn() const {
	return this->turn;
}

const Board* GameState::getRefBoard() const {
	return &(this->board);
}

void GameState::switchTurn() {
	if (this->turn == PieceColor::Black) {
		this->turn = PieceColor::White;
	}
	else {
		this->turn = PieceColor::Black;
	}
}


void GameState::placePiece(PieceName pn, PieceColor pc, const int i, const int j) {
	Piece* piece = nullptr;
	Square* sq = this->getRefBoard()->getSquare(i, j);

	switch (pn)
	{
	case PieceName::None:
		break;
	case PieceName::Pawn:
		piece = new Pawn(pc, sq);
		break;
	case PieceName::Knight:
		piece = new Knight(pc, sq);
		break;
	case PieceName::Bishop:
		piece = new Bishop(pc, sq);
		break;
	case PieceName::Rook:
		piece = new Rook(pc, sq);
		break;
	case PieceName::Queen:
		piece = new Queen(pc, sq);
		break;
	case PieceName::King:
		piece = new King(pc, sq);
		break;
	default:
		break;
	}

	this->board.placePiece(piece, i, j);
}

void GameState::placePiece(PieceName pn, PieceColor pc, const Position& p) {
	this->placePiece(pn, pc, p.get_i(), p.get_j());
}

