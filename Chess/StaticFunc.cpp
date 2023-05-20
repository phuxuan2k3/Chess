#include "StaticFunc.h"




bool isDangerousSquare(const Square* pos, PieceColor color)
{
	// Linear Part - Rook, Bishop, Queen

	Piece* upward = linearSearchEnemy(pos, color, MoveDirection::Up);
	Piece* downward = linearSearchEnemy(pos, color, MoveDirection::Down);
	Piece* leftward = linearSearchEnemy(pos, color, MoveDirection::Left);
	Piece* rightward = linearSearchEnemy(pos, color, MoveDirection::Right);
	Piece* upleft = linearSearchEnemy(pos, color, MoveDirection::UpLeft);
	Piece* upright = linearSearchEnemy(pos, color, MoveDirection::UpRight);
	Piece* downleft = linearSearchEnemy(pos, color, MoveDirection::DownLeft);
	Piece* downright = linearSearchEnemy(pos, color, MoveDirection::DownRight);

	// R - Q
	if (upward != nullptr) {
		if (upward->getPieceName() == PieceName::Queen ||
			upward->getPieceName() == PieceName::Rook)
		{
			return true;
		}
	}
	if (downward != nullptr) {
		if (downward->getPieceName() == PieceName::Queen ||
			downward->getPieceName() == PieceName::Rook)
		{
			return true;
		}
	}
	if (leftward != nullptr) {
		if (leftward->getPieceName() == PieceName::Queen ||
			leftward->getPieceName() == PieceName::Rook)
		{
			return true;
		}
	}
	if (rightward != nullptr) {
		if (rightward->getPieceName() == PieceName::Queen ||
			rightward->getPieceName() == PieceName::Rook)
		{
			return true;
		}
	}

	// B - Q
	if (upleft != nullptr) {
		if (upleft->getPieceName() == PieceName::Queen ||
			upleft->getPieceName() == PieceName::Bishop)
		{
			return true;
		}
	}
	if (upright != nullptr) {
		if (upright->getPieceName() == PieceName::Queen ||
			upright->getPieceName() == PieceName::Bishop)
		{
			return true;
		}
	}
	if (downleft != nullptr) {
		if (downleft->getPieceName() == PieceName::Queen ||
			downleft->getPieceName() == PieceName::Bishop)
		{
			return true;
		}
	}
	if (downright != nullptr) {
		if (downright->getPieceName() == PieceName::Queen ||
			downright->getPieceName() == PieceName::Bishop)
		{
			return true;
		}
	}

	// Short path Part - Pawn, King, Knight
	Piece* test = nullptr;

	// Pawn: Black eat downward, White eat upward
	int pawnEat[2][2] = {
		{-1, -1},
		{-1, 1},
	};
	if (color == PieceColor::Black) {
		pawnEat[0][0] = 1;
		pawnEat[1][0] = 1;
	}
	test = shortSearchEnemy(pos, color, pawnEat, 2);
	if (test != nullptr) {
		if (test->getPieceName() == PieceName::Pawn) {
			return true;
		}
	}

	// Knight
	int knightEat[8][2] = {
		{-2, 1},
		{-2, -1},
		{-1, 2},
		{-1, -2},
		{1, 2},
		{1, -2},
		{2, 1},
		{2, -1},
	};
	test = shortSearchEnemy(pos, color, knightEat, 8);
	if (test != nullptr) {
		if (test->getPieceName() == PieceName::Knight) {
			return true;
		}
	}

	// King
	int kingEat[8][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1},
	};
	test = shortSearchEnemy(pos, color, kingEat, 8);
	if (test != nullptr) {
		if (test->getPieceName() == PieceName::King) {
			return true;
		}
	}

	return false;
}

//===================================================
// Mics
//===================================================

vector<Position> toPos(vector<MovePosition> mp) {
	vector<Position> p;
	for (MovePosition m : mp) {
		p.push_back(m.getPosition());
	}
	return p;
}

//===================================================
// Graphics Related
//===================================================

Position coordinateToPosition(sf::Vector2i coor)
{
	int j = coor.x / 100;
	int i = coor.y / 100;
	return Position(i, j);
}

string getSprite(PieceName pn, PieceColor pc)
{
	switch (pn)
	{
	case PieceName::Pawn:
		if (pc == PieceColor::White)
		{
			return "pt";
		}
		return "p";
		break;
	case PieceName::Knight:
		if (pc == PieceColor::White)
		{
			return "knt";
		}
		return "kn";
		break;
	case PieceName::Bishop:
		if (pc == PieceColor::White)
		{
			return "bt";
		}
		return "b";
		break;
	case PieceName::Rook:
		if (pc == PieceColor::White)
		{
			return "rt";
		}
		return "r";
		break;
	case PieceName::Queen:
		if (pc == PieceColor::White)
		{
			return "qt";
		}
		return "q";
		break;
	case PieceName::King:
		if (pc == PieceColor::White)
		{
			return "kit";
		}
		return "ki";
		break;
	default:
		break;
	}
	return "";
}

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

vector<MovePosition> linearMove(const Square* standOn, PieceColor pieceColor, MoveDirection dir) {
	Square* squareToMove = nullptr;
	vector<MovePosition> pos;

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

vector<MovePosition> shortMove(const Square* standOn, PieceColor pieceColor, int moves[][2]) {
	Square* squareToMove = nullptr;
	vector<MovePosition> pos;

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