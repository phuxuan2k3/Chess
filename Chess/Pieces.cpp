#include "Pieces.h"


//===================================================
// First Move Piece Interface
//===================================================

FirstMovePiece::FirstMovePiece() {
	this->moved = false;
}

// Make sure the event only triggered once
void FirstMovePiece::trigger() {
	if (this->moved == false) {
		this->moved == true;
		action();
	}
}

//===================================================
// Pieces Constructors
//===================================================

Pawn::Pawn(Troop color) : Piece(color)
{
	this->type = PieceType::Pawn;
	this->isFirstMove = true;
}

Knight::Knight(Troop color) : Piece(color)
{
	this->type = PieceType::Knight;
}

Bishop::Bishop(Troop color) : Piece(color)
{
	this->type = PieceType::Bishop;
}

Rook::Rook(Troop color) : Piece(color)
{
	this->type = PieceType::Rook;
	this->kingPiece = nullptr;
}

Queen::Queen(Troop color) : Piece(color)
{
	this->type = PieceType::Queen;
}

King::King(Troop color) : Piece(color)
{
	this->leftRook = nullptr;
	this->rightRook = nullptr;
	this->type = PieceType::King;
	this->castlable = true;
}


//===================================================
// Pawn
//===================================================

void Pawn::action() {
	this->isFirstMove = false;
}

void Pawn::move(const Position& dest)
{
	Piece::move(dest);
	this->trigger();
}

vector<Position> Pawn::canGo()
{
	int inv = 1;
	Square* squareToMove = nullptr;

	vector<Position> pos;

	if (this->color == Troop::White) {
		inv = -1;	// White will go upward
	}
	else {
		inv = 1;	// Black will go downward
	}

	// Checked if it can go 1 or 2 square ahead
	int range = 1;
	if (this->isFirstMove == true) {
		range = 2;
	}

	// Note: If it can't go 1 step, it can never go 2 steps
	for (int i = 1; i <= range; ++i) {
		// If it is nullptr it's out of range
		squareToMove = this->standOn->getRelativeSquare(i * inv, 0);
		if (squareToMove == nullptr) {
			break;
		}
		// If the square is blocked (either it's enemy or our piece)
		if (squareToMove->isEmpty() == false) {
			break;
		}
		pos.push_back(squareToMove->getPosition());
	}
	
	// Eatalbe moves
	// If it's not out of range and has enemy Piece
	squareToMove = this->standOn->getRelativeSquare(1 * inv, 1);
	if (squareToMove != nullptr &&
		squareToMove->isEmpty() == false &&
		squareToMove->getPiece()->getTroop() != this->getTroop()) 
	{
		pos.push_back(squareToMove->getPosition());
	}

	squareToMove = this->standOn->getRelativeSquare(1 * inv, -1);
	if (squareToMove != nullptr &&
		squareToMove->isEmpty() == false &&
		squareToMove->getPiece()->getTroop() != this->getTroop())
	{
		pos.push_back(squareToMove->getPosition());
	}
	return pos;
}

Pawn::~Pawn()
{
}

//===================================================
// Rook
//===================================================

vector<Position> Rook::canGo()
{
	vector<Position> pos;

	vector<Position> upward = linearMove(this->standOn, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<Position> downward = linearMove(this->standOn, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<Position> leftward = linearMove(this->standOn, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<Position> rightward = linearMove(this->standOn, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	return pos;
}

void Rook::move(const Position& dest)
{
	Piece::move(dest);
	this->trigger();
}

void Rook::action() {
	this->kingPiece->setUnCastable();
}

void Rook::setConnection(King* king) {
	// Only connects once
	if (this->kingPiece != nullptr) {
		return;
	}

	// Oops! Wrong connection
	if (king->getTroop() != this->getTroop() ||
		king->getPieceType() != PieceType::King)
	{
		throw WrongConnection();
	}

	this->kingPiece = king;
}

//===================================================
// Knight
//===================================================

vector<Position> Knight::canGo() {
	int moves[8][2] = { 
		{-2, 1},
		{-2, -1},
		{-1, 2},
		{-1, -2},
		{1, 2},
		{1, -2},
		{2, 1},
		{2, -1},
	};
	return shortMove(this->standOn, this->color, moves);
}

//===================================================
// Bishop
//===================================================

vector<Position> Bishop::canGo()
{
	vector<Position> pos;

	vector<Position> upleft = linearMove(this->standOn, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<Position> upright = linearMove(this->standOn, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<Position> downleft = linearMove(this->standOn, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<Position> downright = linearMove(this->standOn, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// Queen
//===================================================

vector<Position> Queen::canGo()
{
	vector<Position> pos;

	vector<Position> upward = linearMove(this->standOn, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<Position> downward = linearMove(this->standOn, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<Position> leftward = linearMove(this->standOn, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<Position> rightward = linearMove(this->standOn, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	vector<Position> upleft = linearMove(this->standOn, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<Position> upright = linearMove(this->standOn, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<Position> downleft = linearMove(this->standOn, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<Position> downright = linearMove(this->standOn, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// King
//===================================================

void King::setUnCastable() {
	this->castlable == false;
}

void King::setConnection(Rook* lR, Rook* rR) {
	// Only connects once
	if (this->leftRook != nullptr || this->rightRook != nullptr) {
		return;
	}

	// Oops! Wrong connection
	if (lR->getTroop() != this->getTroop() ||
		rR->getTroop() != this->getTroop() ||
		lR->getPieceType() != PieceType::Rook ||
		rR->getPieceType() != PieceType::Rook) 
	{
		throw WrongConnection();
	}

	this->leftRook = lR;
	this->rightRook = rR;
}

void King::action() {
	this->castlable = false;
}

vector<Position> King::canGo()
{
	vector<Position> pos;
	int moves[8][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1},
	};
	pos = shortMove(this->standOn, this->color, moves);
	
	// Handle castling
	if (this->castlable == false) {
		return pos;
	}
	// goto with do - while style
	do {

		// Note: If the king hasn't moved, all relative square that we get below will always
		// valid. Therefore, no need for checking nullptr.
		Square* s_1;	// One square away
		Square* s_2;	// Two square away
		Square* s_3;	// Three square away


		// Left castling: R K B Q Ki
		// 3 Squares on the left
		s_1 = this->standOn->getRelativeSquare(0, -1);
		s_2 = this->standOn->getRelativeSquare(0, -2);
		s_3 = this->standOn->getRelativeSquare(0, -3);

		// The Path must be empty
		if (s_1->isEmpty() == true &&
			s_2->isEmpty() == true &&
			s_3->isEmpty() == true)
		{
			// Check squares that King go pass by is Dangerous
			if (isDangerousSquare(
				this->standOn,
				this->color
			) == false &&
				isDangerousSquare(
					s_1,
					this->color
				) == false &&
				isDangerousSquare(
					s_2,
					this->color
				) == false)
			{
				// End checking, add the postion if it satifies all conditions above
				pos.push_back(Position(s_2->getPosition(), PosInfo::CastlingLeft));
			}
		}


		// Right castling: Ki B K R
		// 2 Squares on the Right
		s_1 = this->standOn->getRelativeSquare(0, 1);
		s_2 = this->standOn->getRelativeSquare(0, 2);

		// The Path must be empty
		if (s_1->isEmpty() == true &&
			s_2->isEmpty() == true)
		{
			// Check squares that King go pass by is Dangerous
			if (isDangerousSquare(
				this->standOn,
				this->color
			) == false &&
				isDangerousSquare(
					s_1,
					this->color
				) == false &&
				isDangerousSquare(
					s_2,
					this->color
				) == false)
			{
				// End checking, add the postion if it satifies all conditions above
				pos.push_back(Position(s_2->getPosition(), PosInfo::CastlingRight));
			}
		}

	} while (false);

	return pos;
}

void King::move(const Position& dest)
{
	if (dest.getMoveType() == PosInfo::CastlingLeft) {
		this->leftRook->move(this->standOn->getRelativeSquare(0, -1)->getPosition());
	}
	else if (dest.getMoveType() == PosInfo::CastlingRight) {
		this->rightRook->move(this->standOn->getRelativeSquare(0, 1)->getPosition());
	}
	Piece::move(dest);
	this->trigger();
}
