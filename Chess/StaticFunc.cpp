#include "StaticFunc.h"




bool isDangerousSquare(const Position& src, const Board& board, Troop color)
{
	// Linear Part - Rook, Bishop, Queen

	Piece* upward = linearSearchEnemy(src, board, color, MoveDirection::Up);
	Piece* downward = linearSearchEnemy(src, board, color, MoveDirection::Down);
	Piece* leftward = linearSearchEnemy(src, board, color, MoveDirection::Left);
	Piece* rightward = linearSearchEnemy(src, board, color, MoveDirection::Right);
	Piece* upleft = linearSearchEnemy(src, board, color, MoveDirection::UpLeft);
	Piece* upright = linearSearchEnemy(src, board, color, MoveDirection::UpRight);
	Piece* downleft = linearSearchEnemy(src, board, color, MoveDirection::DownLeft);
	Piece* downright = linearSearchEnemy(src, board, color, MoveDirection::DownRight);

	// R - Q
	if (upward != nullptr) {
		if (upward->getPieceType() == PieceType::Queen ||
			upward->getPieceType() == PieceType::Rook)
		{
			return true;
		}
	}
	if (downward != nullptr) {
		if (downward->getPieceType() == PieceType::Queen ||
			downward->getPieceType() == PieceType::Rook)
		{
			return true;
		}
	}
	if (leftward != nullptr) {
		if (leftward->getPieceType() == PieceType::Queen ||
			leftward->getPieceType() == PieceType::Rook)
		{
			return true;
		}
	}
	if (rightward != nullptr) {
		if (rightward->getPieceType() == PieceType::Queen ||
			rightward->getPieceType() == PieceType::Rook)
		{
			return true;
		}
	}

	// B - Q
	if (upleft != nullptr) {
		if (upleft->getPieceType() == PieceType::Queen ||
			upleft->getPieceType() == PieceType::Bishop)
		{
			return true;
		}
	}
	if (upright != nullptr) {
		if (upright->getPieceType() == PieceType::Queen ||
			upright->getPieceType() == PieceType::Bishop)
		{
			return true;
		}
	}
	if (downleft != nullptr) {
		if (downleft->getPieceType() == PieceType::Queen ||
			downleft->getPieceType() == PieceType::Bishop)
		{
			return true;
		}
	}
	if (downright != nullptr) {
		if (downright->getPieceType() == PieceType::Queen ||
			downright->getPieceType() == PieceType::Bishop)
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
	if (color == Troop::Black) {
		pawnEat[0][0] = 1;
		pawnEat[1][0] = 1;
	}
	test = shortSearchEnemy(src, board, color, pawnEat, 2);
	if (test != nullptr) {
		if (test->getPieceType() == PieceType::Pawn) {
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
	test = shortSearchEnemy(src, board, color, knightEat, 8);
	if (test != nullptr) {
		if (test->getPieceType() == PieceType::Knight) {
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
	test = shortSearchEnemy(src, board, color, kingEat, 8);
	if (test != nullptr) {
		if (test->getPieceType() == PieceType::King) {
			return true;
		}
	}

	return false;
}

//===================================================
// Mics
//===================================================

int hasPosition(vector<Position> list, Position item)
{
	for (int i = 0; i < list.size(); ++i) {
		if (list[i].isPosEqual(item)) {
			return i;
		}
	}
	return -1;
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

string getSprite(PieceType pn, Troop pc)
{
	switch (pn)
	{
	case PieceType::Pawn:
		if (pc == Troop::White)
		{
			return "pt";
		}
		return "p";
		break;
	case PieceType::Knight:
		if (pc == Troop::White)
		{
			return "knt";
		}
		return "kn";
		break;
	case PieceType::Bishop:
		if (pc == Troop::White)
		{
			return "bt";
		}
		return "b";
		break;
	case PieceType::Rook:
		if (pc == Troop::White)
		{
			return "rt";
		}
		return "r";
		break;
	case PieceType::Queen:
		if (pc == Troop::White)
		{
			return "qt";
		}
		return "q";
		break;
	case PieceType::King:
		if (pc == Troop::White)
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

Piece* linearSearchEnemy(const Position& src, const Board& board, Troop troop, MoveDirection dir) {
	Position squareToMove;

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
		squareToMove = src.getRelativePosition(range_i, range_j);

		// If it's out of range
		if (squareToMove.isNotNull() == false) {
			break;
		}
		// If it's blocked by a Piece
		if (board.hasPiece(squareToMove) == true) {
			Piece* blocker = board.getPiece(squareToMove);
			// Enemy Piece
			if (blocker->getTroop() != troop) {
				// Found Enemy
				return blocker;
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
Piece* shortSearchEnemy(const Position& src, const Board& board, Troop troop, int moves[][2], int range) {
	Position squareToMove;

	for (int i = 0; i < range; ++i) {
		squareToMove = src.getRelativePosition(moves[i][0], moves[i][1]);

		// If it's out of range
		if (squareToMove.isNotNull() == false) {
			continue;
		}
		// If it's blocked by a Piece
		if (board.hasPiece(squareToMove) == true) {
			Piece* blocker = board.getPiece(squareToMove);
			// Found 1 enemy
			if (blocker->getTroop() != troop) {
				return blocker;
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

vector<Position> linearMove(const Position& src, const Board& board, Troop troop, MoveDirection dir) {
	Position squareToMove;
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
		squareToMove = src.getRelativePosition(range_i, range_j);

		// If it's out of range
		if (squareToMove.isNotNull() == false) {
			break;
		}
		// If it's blocked by a Piece
		if (board.hasPiece(squareToMove) == true) {
			Piece* blocker = board.getPiece(squareToMove);
			// Enemy Piece
			if (blocker->getTroop() != troop) {
				pos.push_back(squareToMove);
				break;
			}
			// Our Piece
			else {
				break;
			}
		}
		pos.push_back(squareToMove);
	}
	return pos;
}

vector<Position> shortMove(const Position& src, const Board& board, Troop troop, int moves[][2]) {
	Position squareToMove;
	vector<Position> pos;

	// 8 is the number of moves for King and Knight
	for (int i = 0; i < 8; ++i) {
		squareToMove = src.getRelativePosition(moves[i][0], moves[i][1]);

		// If it's out of range
		if (squareToMove.isNotNull() == false) {
			continue;
		}
		// If it's blocked by a Piece
		if (board.hasPiece(squareToMove) == true) {
			// Our Piece
			if (board.getPiece(squareToMove)->getTroop() == troop) {
				continue;
			}
		}
		pos.push_back(squareToMove);
	}

	return pos;
}