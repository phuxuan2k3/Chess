#include "Game.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(Troop turn) {
	this->turn = turn;

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
	((King*)this->board.getPiece(0, 4))->setRooksPosition(
		Position(0,0),
		Position(0,7)
	);
	// White Side
	((King*)this->board.getPiece(7, 4))->setRooksPosition(
		Position(7, 0),
		Position(7, 7)
	);

}

GameState::~GameState()
{
	for (Piece* p : this->pieces) {
		delete p;
	}
}

void GameState::switchTurn() {
	if (this->turn == Troop::Black) {
		this->turn = Troop::White;
	}
	else {
		this->turn = Troop::Black;
	}
}

const Board* GameState::getRefBoard() const {
	return &this->board;
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j) {
	Piece* piece = nullptr;
	switch (pn)
	{
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

	this->board.setPiece(i, j, piece);
	return piece;
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const Position& p) {
	return this->initPieceOnBoard(pn, pc, p.get_i(), p.get_j());
}

bool GameState::isValidChoice(const Position& pos) const {
	Piece* piece = this->board.getPiece(pos);
	// If there isn't any piece
	if (piece == nullptr) {
		return false;
	}
	// Not valid turn
	if (piece->getTroop() != this->turn) {
		return false;
	}
	return true;
}

vector<Position> GameState::canGo(const Position& pos) {
	if (this->board.hasPiece(pos) == false) {
		return vector<Position>();
	}
	return this->board.getPiece(pos)->canGo(pos, this->board);
}

bool GameState::isValidMove(const Position& src, const Position& dest, vector<Position> canGo) const {
	// If the src Square chosen is empty, we do nothing
	if (this->board.hasPiece(src) == false) {
		return false;
	}
	// If dest Square is not in canGo
	if (hasPosition(canGo, dest) == -1) {
		return false;
	}
	return true;
}

void GameState::move(const Position& src, const Position& dest, vector<Position> canGo) {
	// Normal Move:
	Piece* pSrc = this->board.getPiece(src);
	pSrc->triggerOnFirstMove();
	// If dest Square is occupied by a Piece
	if (this->board.hasPiece(dest) == true) {
		this->board.getPiece(dest)->setNull();
	}
	this->board.setPiece(dest, pSrc);
	this->board.setPiece(src, nullptr);
	this->board.lastChoose = pSrc;
	// Castling Move:

	if (pSrc->getTroop() == Troop::White) {
		this->board.EnPassantWhite = false;
	}
	else {
		this->board.EnPassantBlack = false;
	}


	if (dest.getInfo() == PosInfo::CastlingLeft) {
		this->move(((King*)pSrc)->getLeftRook(), src.getRelativePosition(0, -1), canGo);
	}
	else if (dest.getInfo() == PosInfo::CastlingRight) {
		this->move(((King*)pSrc)->getRightRook(), src.getRelativePosition(0, 1), canGo);
	} 
	else if (dest.getInfo() == PosInfo::FirstPawnMove) {
		if (pSrc->getTroop() == Troop::White) {
			this->board.EnPassantBlack = true;
		}
		else {
			this->board.EnPassantWhite = true;
		}
	}
	else if (dest.getInfo() == PosInfo::EnPassant) {
		int dir = (pSrc->getTroop() == Troop::White ? 1 : -1);
		this->board.getPiece(dest.getRelativePosition(dir, 0))->setNull();
		this->board.setPiece(dest.getRelativePosition(dir,0), nullptr);
	}

	cout << "Black: " << this->board.EnPassantBlack << endl;
	cout << "White: " << this->board.EnPassantWhite << endl;
}