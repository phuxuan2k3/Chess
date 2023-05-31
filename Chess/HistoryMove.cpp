#include "HistoryMove.h"
#include "Pieces.h"


//========================================================
// Move Event
//========================================================


MoveEvent::MoveEvent(Piece* mover, const Position& srcPos, const Position& desPos, Piece* eaten, const Position& eatPos) {
	this->preInfoPiece = mover->deepCopyPiece(mover);
	this->moverPiece = mover;
	this->eatenPiece = eaten;
	this->srcPos = srcPos;
	this->destPos = desPos;
	this->eatPos = eatPos;
}

MoveEvent::~MoveEvent()
{
	delete this->preInfoPiece;
}

bool MoveEvent::isEatMove() const {
	return this->eatenPiece != nullptr &&
		this->eatPos.isNotNull() == true;
}

void MoveEvent::loadMoverInfo(Piece* const p) const {
	p->set(this->preInfoPiece);
}

Piece* MoveEvent::reviveEaten() const {
	return this->eatenPiece;
}

Position MoveEvent::getMoverSrc() const {
	return this->srcPos;
}

Position MoveEvent::getMoverDest() const {
	return this->destPos;
}

Position MoveEvent::getEatenPos() const {
	return this->eatPos;
}

Piece* MoveEvent::getMover() const {
	return this->moverPiece;
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

void MoveHistory::append(Piece* mover, const Position& srcPos, const Position& desPos, Piece* eaten, const Position& eatPos)
{
	this->moves.push_back(new MoveEvent(mover, srcPos, desPos, eaten, eatPos));
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
void MoveHistory::truncate() {
	while (this->state + 1 < this->moves.size() && this->moves.empty() == false) {
		delete this->moves.back();
		this->moves.pop_back();
	}
}

