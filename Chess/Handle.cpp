#include "Handle.h"


// Observer (???)

bool GameHandle::isDangerousSquare(const Square* pos, PieceColor color)
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