#include "HistoryMove.h"
#include "Pieces.h"


//========================================================
// Move Event
//========================================================

MoveEvent::MoveEvent(Piece* mover,  const Position& srcPos, const Position& desPos, Piece* lastChoose) {
	this->moverPiece = mover;
	this->srcPos = srcPos;
	this->destPos = desPos;

	this->copySrcPiece = nullptr;
	this->copyDestPiece = nullptr;

	this->eatenPiece = nullptr;
	this->eatPos = Position();

	this->castRookMove = nullptr;

	this->promotePiece = nullptr;
	this->promPos = Position();

	this->lastChoose = lastChoose;
}

MoveEvent::~MoveEvent()
{
	delete this->copySrcPiece;
	delete this->copyDestPiece;
	delete this->castRookMove;
}

void MoveEvent::saveSrcPieceInfo(Piece* const p) {
	this->copySrcPiece = p->deepCopyPiece(p);
}

void MoveEvent::saveDestPieceInfo(Piece* const p) {
	this->copyDestPiece = p->deepCopyPiece(p);
}

void MoveEvent::loadSrcPieceInfo(Piece* const p) const {
	p->set(this->copySrcPiece);
}

void MoveEvent::loadDestPieceInfo(Piece* const p) const {
	p->set(this->copyDestPiece);
}

Piece* MoveEvent::getMoverPiece() const {
	return this->moverPiece;
}

Position MoveEvent::getSrcPos() const {
	return this->srcPos;
}

Position MoveEvent::getDestPos() const {
	return this->destPos;
}

// Eat =======

bool MoveEvent::isEatMove() const {
	return this->eatenPiece != nullptr &&
		this->eatPos.isNotNull() == true;
}

Piece* MoveEvent::getEatenPiece() const {
	return this->eatenPiece;
}

Position MoveEvent::getEatenPos() const {
	return this->eatPos;
}

void MoveEvent::setEatMove(Piece* eaten, const Position& pos) {
	this->eatenPiece = eaten;
	this->eatPos = pos;
}

// Castling =======

bool MoveEvent::isCastlingMove() const {
	return this->castRookMove != nullptr;
}

MoveEvent* MoveEvent::getCastRookMove() const {
	return this->castRookMove;
}

void MoveEvent::setCastRookMove(MoveEvent* castle) {
	this->castRookMove = castle;
}

// Promote =======

bool MoveEvent::isPromoteMove() const {
	return this->promotePiece != nullptr &&
		this->promPos.isNotNull() == true;
}

Piece* MoveEvent::getPromotePiece() const {
	return this->promotePiece;
}

Position MoveEvent::getPromotePos() const {
	return this->promPos;
}

void MoveEvent::setPromote(Piece* promote, const Position& pos) {
	this->promotePiece = promote;
	this->promPos = pos;
}

// Last Choose ======

Piece* MoveEvent::getLastChoosePiece() const {
	return this->lastChoose;
}


//========================================================
// Move History
//========================================================


MoveHistory::MoveHistory()
{
	this->state = -1;
}

MoveHistory::~MoveHistory() {
	for (MoveEvent* move : this->moves) {
		delete move;
		move = nullptr;
	}
}

void MoveHistory::append(Piece* mover, const Position& srcPos, const Position& desPos, Piece* lastChoose)
{
	this->moves.push_back(new MoveEvent(mover, srcPos, desPos, lastChoose));
	this->state++;
}

MoveEvent* MoveHistory::getCur() const {
	if (this->state <= -1 || this->state >= this->moves.size()) {
		return nullptr;
	}
	return this->moves.at(state);
}

void MoveHistory::goBack() {
	if (this->state >= 0) {
		this->state -= 1;
	}
}

void MoveHistory::goOn() {
	if (this->state < this->moves.size() - 1) {
		this->state += 1;
	}
}

// Truncate till state + 1 = size
void MoveHistory::truncate(vector<Piece*> pieceNew) {
	while (this->state + 1 < this->moves.size() && this->moves.empty() == false) {
		// Delete the Piece from manage vector
		if (this->moves.back()->isPromoteMove() == true) {
			for (int i = 0; i < pieceNew.size(); ++i) {
				if (pieceNew[i] == this->moves.back()->getPromotePiece()) {
					pieceNew.erase(pieceNew.begin() + i);
				}
			}
		}
		delete this->moves.back();
		this->moves.pop_back();
	}
}

