#include "StaticFunc.h"



//===================================================
// Find enemy
//===================================================

Piece* linearSearchEnemy(const Square* standOn, PieceColor pieceColor, MoveDirection dir) {
	Square* squareToMove = nullptr;

	int range_i = 0;
	int range_j = 0;
	int i = 0;
	int j = 0;

	switch (dir)
	{
	case MoveDirection::Up:
		i = -1;
		j = 0;
		break;
	case MoveDirection::Down:
		i = 1;
		j = 0;
		break;
	case MoveDirection::Left:
		i = 0;
		j = -1;
		break;
	case MoveDirection::Right:
		i = 0;
		j = 1;
		break;
	case MoveDirection::UpLeft:
		i = -1;
		j = -1;
		break;
	case MoveDirection::UpRight:
		i = -1;
		j = 1;
		break;
	case MoveDirection::DownLeft:
		i = 1;
		j = -1;
		break;
	case MoveDirection::DownRight:
		i = 1;
		j = 1;
		break;
	default:
		break;
	}

	while (true) {
		range_i += i;
		range_j += j;
		squareToMove = standOn->getRelativeSquare(range_i, range_j);

		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != pieceColor) {
				// Found Enemy
				return squareToMove->getPiece();
			}
			// Our Piece
			else {
				break;
			}
		}
	}
	// Doesn't Found
	return nullptr;
}

// Count the Pawn case, cause it 
Piece* shortSearchEnemy(const Square* standOn, PieceColor pieceColor, int moves[][2], int range) {
	Square* squareToMove = nullptr;

	for (int i = 0; i < range; ++i) {
		squareToMove = standOn->getRelativeSquare(moves[i][0], moves[i][1]);

		// If it's out of range
		if (squareToMove == nullptr) {
			continue;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// Found enemy
			if (squareToMove->getPiece()->getPieceColor() != pieceColor) {
				return squareToMove->getPiece();
			}
			else {
				continue;
			}
		}
	}

	return nullptr;
}

//===================================================
// Moves
//===================================================

vector<Position> linearMove(const Square* standOn, PieceColor pieceColor, MoveDirection dir) {
	Square* squareToMove = nullptr;
	vector<Position> pos;

	int range_i = 0;
	int range_j = 0;
	int i = 0;
	int j = 0;

	switch (dir)
	{
	case MoveDirection::Up:
		i = -1;
		j = 0;
		break;
	case MoveDirection::Down:
		i = 1;
		j = 0;
		break;
	case MoveDirection::Left:
		i = 0;
		j = -1;
		break;
	case MoveDirection::Right:
		i = 0;
		j = 1;
		break;
	case MoveDirection::UpLeft:
		i = -1;
		j = -1;
		break;
	case MoveDirection::UpRight:
		i = -1;
		j = 1;
		break;
	case MoveDirection::DownLeft:
		i = 1;
		j = -1;
		break;
	case MoveDirection::DownRight:
		i = 1;
		j = 1;
		break;
	default:
		break;
	}

	while (true) {
		range_i += i;
		range_j += j;
		squareToMove = standOn->getRelativeSquare(range_i, range_j);

		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != pieceColor) {
				pos.push_back(squareToMove->getPosition());
				break;
			}
			// Our Piece
			else {
				break;
			}
		}
		pos.push_back(squareToMove->getPosition());
	}
	return pos;
}

vector<Position> shortMove(const Square* standOn, PieceColor pieceColor, int moves[][2]) {
	Square* squareToMove = nullptr;
	vector<Position> pos;

	// 8 is the number of moves for King and Knight
	for (int i = 0; i < 8; ++i) {
		squareToMove = standOn->getRelativeSquare(moves[i][0], moves[i][1]);

		// If it's out of range
		if (squareToMove == nullptr) {
			continue;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// Our Piece
			if (squareToMove->getPiece()->getPieceColor() == pieceColor) {
				continue;
			}
		}
		pos.push_back(squareToMove->getPosition());
	}

	return pos;
}