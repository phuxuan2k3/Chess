#include "Pieces.h"



FirstMovePiece::FirstMovePiece() {
	this->moved = false;
}

bool FirstMovePiece::hasNotMoved() const {
	return !this->moved;
}

// It has been moved, no need to set back to false
void FirstMovePiece::setMoved() {
	this->moved = true;
}

//===================================================
// Pieces Constructors
//===================================================

Pawn::Pawn(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->type = PieceName::Pawn;
}

Knight::Knight(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->type = PieceName::Knight;
}

Bishop::Bishop(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->type = PieceName::Bishop;
}

Rook::Rook(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->type = PieceName::Rook;
}

Queen::Queen(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->type = PieceName::Queen;
}

King::King(PieceColor color, Square* stand) : Piece(color, stand)
{
	this->leftRook = nullptr;
	this->rightRook = nullptr;
	this->type = PieceName::King;
}


//===================================================
// Pawn
//===================================================

void Pawn::move(const MovePosition& dest)
{
	Piece::move(dest);
	this->setMoved();
}

vector<MovePosition> Pawn::canGo()
{
	int inv = 1;
	Square* squareToMove = nullptr;

	vector<MovePosition> pos;

	if (this->color == PieceColor::White) {
		inv = -1;	// White will go upward
	}
	else {
		inv = 1;	// Black will go downward
	}

	// Checked if it can go 1 or 2 square ahead
	int range = 1;
	if (this->hasNotMoved() == true) {
		range = 2;
	}

	// Note: If it can't go 1 step, it can never go 2 steps
	for (int i = 1; i <= 2; ++i) {
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
		squareToMove->getPiece()->getPieceColor() != this->getPieceColor()) 
	{
		pos.push_back(squareToMove->getPosition());
	}

	squareToMove = this->standOn->getRelativeSquare(1 * inv, -1);
	if (squareToMove != nullptr &&
		squareToMove->isEmpty() == false &&
		squareToMove->getPiece()->getPieceColor() != this->getPieceColor())
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

vector<MovePosition> Rook::canGo()
{
	vector<MovePosition> pos;

	vector<MovePosition> upward = linearMove(this->standOn, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<MovePosition> downward = linearMove(this->standOn, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<MovePosition> leftward = linearMove(this->standOn, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<MovePosition> rightward = linearMove(this->standOn, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	return pos;
}

void Rook::move(const MovePosition& dest)
{
	Piece::move(dest);
	this->setMoved();
}

//===================================================
// Knight
//===================================================

vector<MovePosition> Knight::canGo() {
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

vector<MovePosition> Bishop::canGo()
{
	vector<MovePosition> pos;

	vector<MovePosition> upleft = linearMove(this->standOn, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<MovePosition> upright = linearMove(this->standOn, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<MovePosition> downleft = linearMove(this->standOn, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<MovePosition> downright = linearMove(this->standOn, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// Queen
//===================================================

vector<MovePosition> Queen::canGo()
{
	vector<MovePosition> pos;

	vector<MovePosition> upward = linearMove(this->standOn, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<MovePosition> downward = linearMove(this->standOn, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<MovePosition> leftward = linearMove(this->standOn, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<MovePosition> rightward = linearMove(this->standOn, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	vector<MovePosition> upleft = linearMove(this->standOn, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<MovePosition> upright = linearMove(this->standOn, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<MovePosition> downleft = linearMove(this->standOn, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<MovePosition> downright = linearMove(this->standOn, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// King
//===================================================

vector<MovePosition> King::canGo()
{
	vector<MovePosition> pos;
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

	// goto with do - while style
	do {
		// Handle castling
		// King has moved => no castling
		if (this->hasNotMoved() == false) {
			break;
		}
		// Note: If the king hasn't moved, all relative square that we get below will always
		// valid. Therefore, no need for checking nullptr.

		Square* s_1;	// One square away
		Square* s_2;	// Two square away
		Square* s_3;	// Three square away

		// Left castling: R K B Q Ki
		Piece* leftRook = this->standOn->getRelativeSquare(0, -4)->getPiece();
		
		s_1 = this->standOn->getRelativeSquare(0, -1);
		s_2 = this->standOn->getRelativeSquare(0, -2);
		s_3 = this->standOn->getRelativeSquare(0, -3);

		if (
			// It's Rook
			leftRook != nullptr &&
			leftRook->getPieceName() != PieceName::Rook &&
			// It's our troop
			leftRook->getPieceColor() == this->color &&
			// Left Rook has not moved
			((Rook*)leftRook)->hasNotMoved() == true &&
			// Check 3 squares that on the left path must bve empty
			(
				s_1->isEmpty() == true &&
				s_2->isEmpty() == true &&
				s_3->isEmpty() == true
			) && 
			// Check squares that King go pass by is Dangerous
			(
				isDangerousSquare(
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
			) == false
			)
			// End checking, add the postion if it satifies all conditions above
			)
		{
			pos.push_back(s_2->getPosition());
		}
			

		// Right castling: Ki B K R
		Piece* rightRook = this->standOn->getRelativeSquare(0, -4)->getPiece();
		
		s_1 = this->standOn->getRelativeSquare(0, 1);
		s_2 = this->standOn->getRelativeSquare(0, 2);

		if (
			// It's Rook
			rightRook != nullptr &&
			rightRook->getPieceName() != PieceName::Rook &&
			// It's our troop
			rightRook->getPieceColor() == this->color &&
			// Left Rook has not moved
			((Rook*)rightRook)->hasNotMoved() == true &&
			// Check 3 squares that on the left path must bve empty
			(
				s_1->isEmpty() == true &&
				s_2->isEmpty() == true
			) && 
			// Check squares that King go pass by is Dangerous
			(
				isDangerousSquare(
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
			) == false
			)
			// End checking, add the postion if it satifies all conditions above
			)
		{
			pos.push_back(s_2->getPosition());
		}
	} while (false);

	return pos;
}

void King::move(const MovePosition& dest)
{
	if (dest.getMoveType() == MoveType::CastlingLeft) {
		this->leftRook->move(this->standOn->getRelativeSquare(0, -1)->getPosition());
	}
	else if (dest.getMoveType() == MoveType::CastlingRight) {
		this->leftRook->move(this->standOn->getRelativeSquare(0, 1)->getPosition());
	}
	Piece::move(dest);
	this->setMoved();
}
