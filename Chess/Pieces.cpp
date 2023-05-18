#include "Pieces.h"


//===================================================
// Pieces Constructors
//===================================================

Pawn::Pawn(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::Pawn;
}

Knight::Knight(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::Knight;
}

Bishop::Bishop(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::Bishop;
}

Rook::Rook(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::Rook;
}

Queen::Queen(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::Queen;
}

King::King(PieceColor color, const Square* stand, int id) : Piece(color, stand, id)
{
	this->type = PieceName::King;
}


//===================================================
// Pawn
//===================================================

void Pawn::move(const Position& dest)
{
	Piece::move(dest);
	this->isFirstMove = false;
}

vector<Position> Pawn::canGo()
{
	int inv = 1;
	Square* squareToMove = nullptr;

	vector<Position> pos;

	if (this->color == PieceColor::White) {
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
	this->isFirstMove = false;
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

	// goto with do - while style
	do {
		// Handle castling
		// King has moved => no castling
		if (this->isFirstMove == false) {
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
			((Rook*)leftRook)->isFirstMove == true &&
			// Check 3 squares that on the left path must bve empty
			(
				s_1->isEmpty() == true &&
				s_2->isEmpty() == true &&
				s_3->isEmpty() == true
			) && 
			// Check squares that King go pass by is Dangerous
			(
				GameHandle::isDangerousSquare(
					this->standOn,
					this->color
			) == false &&
				GameHandle::isDangerousSquare(
					s_1,
					this->color
			) == false &&
				GameHandle::isDangerousSquare(
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
			((Rook*)rightRook)->isFirstMove == true &&
			// Check 3 squares that on the left path must bve empty
			(
				s_1->isEmpty() == true &&
				s_2->isEmpty() == true
			) && 
			// Check squares that King go pass by is Dangerous
			(
				GameHandle::isDangerousSquare(
					this->standOn,
					this->color
			) == false &&
				GameHandle::isDangerousSquare(
					s_1,
					this->color
			) == false &&
				GameHandle::isDangerousSquare(
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

void King::move(const Position& dest)
{
	Piece::move(dest);
	this->isFirstMove = false;
}
