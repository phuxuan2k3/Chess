#include "Pieces.h"



//PieceConnection::PieceConnection() 
//{
//}
//
//void PieceConnection::setConnection(const Position& dest) {
//	this->dest = dest;
//}
//
//Position PieceConnection::getDestPosition() const {
//	return this->dest;
//}

Castling::Castling() {
	this->castlable = true;
}

void Castling::setCastlable(bool c)
{
	this->castlable = c;
}

void Castling::unCastlable() {
	this->castlable = false;
}

bool Castling::isCastlable() const {
	return this->castlable;
}

//===================================================
// Pieces Constructors
//===================================================

Pawn::Pawn(Troop color) : Piece(color)
{
	this->type = PieceType::Pawn;
	this->pawnFirstMove = true;
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
}

Queen::Queen(Troop color) : Piece(color)
{
	this->type = PieceType::Queen;
}

King::King(Troop color) : Piece(color)
{
	this->type = PieceType::King;
}


//===================================================
// Pawn
//===================================================

void Pawn::triggerOnFirstMove() {
	this->pawnFirstMove = false;
}

vector<Position> Pawn::canGo(const Position& src, const Board& board)
{
	int endBoard = 0;
	int inv = 1;
	Position squareToMove;
	vector<Position> pos;


	if (this->color == Troop::White) {
		inv = -1;	// White will go upward
		endBoard = 0;
	}
	else {
		inv = 1;	// Black will go downward
		endBoard = 7;
	}

	// Checked if it can go 1 or 2 square ahead
	int range = 1;
	if (this->pawnFirstMove == true) {
		range = 2;
	}

	// Note: If it can't go 1 step, it can never go 2 steps
	for (int i = 1; i <= range; ++i) {
		// If it is nullptr it's out of range
		squareToMove = src.getRelativePosition(i * inv, 0);
		if (squareToMove.isNotNull() == false) {
			break;
		}
		// If the square is blocked (either it's enemy or our piece)
		if (board.hasPiece(squareToMove) == true) {
			break;
		}
		if (squareToMove.get_i() == endBoard)  squareToMove.setMoveType(PosInfo::Promote);
		if (i == 2) squareToMove.setMoveType(PosInfo::PawnMovedTwoStep);
		pos.push_back(squareToMove);

	}

	// Eatalbe moves
	squareToMove = src.getRelativePosition(1 * inv, 1);
	// If it's not out of range and has enemy Piece
	if (squareToMove.isNotNull() == true &&
		board.hasPiece(squareToMove) == true &&
		board.getPiece(squareToMove)->getTroop() != this->getTroop())
	{
		if (squareToMove.get_i() == endBoard)  squareToMove.setMoveType(PosInfo::Promote);
		pos.push_back(squareToMove);
	}

	squareToMove = src.getRelativePosition(1 * inv, -1);
	// If it's not out of range and has enemy Piece
	if (squareToMove.isNotNull() == true &&
		board.hasPiece(squareToMove) == true &&
		board.getPiece(squareToMove)->getTroop() != this->getTroop())
	{
		if (squareToMove.get_i() == endBoard)  squareToMove.setMoveType(PosInfo::Promote);
		pos.push_back(squareToMove);
	}

	bool canEnPassant = (this->color == Troop::Black ? board.EnPassantBlack : board.EnPassantWhite);

	squareToMove = src.getRelativePosition(1 * inv, -1);
	if (squareToMove.isNotNull() == true &&
		board.hasPiece(src.getRelativePosition(0, -1)) &&
		board.getPiece(src.getRelativePosition(0, -1))->getPieceType() == PieceType::Pawn &&
		board.getPiece(src.getRelativePosition(0, -1)) == board.lastChoose &&
		squareToMove.isNotNull() == true &&
		canEnPassant == true &&
		board.getPiece(src.getRelativePosition(0, -1))->getTroop() != board.getPiece(src)->getTroop()
		) {
		squareToMove.setMoveType(PosInfo::EnPassant);
		pos.push_back(squareToMove);
	}

	squareToMove = src.getRelativePosition(1 * inv, 1);
	if (squareToMove.isNotNull() == true &&
		board.hasPiece(src.getRelativePosition(0, 1)) &&
		board.getPiece(src.getRelativePosition(0, 1))->getPieceType() == PieceType::Pawn &&
		board.getPiece(src.getRelativePosition(0, 1)) == board.lastChoose &&
		squareToMove.isNotNull() == true &&
		canEnPassant == true &&
		board.getPiece(src.getRelativePosition(0, 1))->getTroop() != board.getPiece(src)->getTroop()
		) {
		squareToMove.setMoveType(PosInfo::EnPassant);
		pos.push_back(squareToMove);
	}

	return pos;
}

Pawn::~Pawn()
{
}

//===================================================
// Rook
//===================================================

vector<Position> Rook::canGo(const Position& src, const Board& board)
{
	vector<Position> pos;

	vector<Position> upward = linearMove(src, board, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<Position> downward = linearMove(src, board, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<Position> leftward = linearMove(src, board, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<Position> rightward = linearMove(src, board, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	return pos;
}

void Rook::triggerOnFirstMove() {
	this->unCastlable();
}

//===================================================
// Knight
//===================================================

vector<Position> Knight::canGo(const Position& src, const Board& board) {
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
	return shortMove(src, board, this->color, moves);
}

//===================================================
// Bishop
//===================================================

vector<Position> Bishop::canGo(const Position& src, const Board& board)
{
	vector<Position> pos;

	vector<Position> upleft = linearMove(src, board, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<Position> upright = linearMove(src, board, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<Position> downleft = linearMove(src, board, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<Position> downright = linearMove(src, board, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// Queen
//===================================================

vector<Position> Queen::canGo(const Position& src, const Board& board)
{
	vector<Position> pos;

	vector<Position> upward = linearMove(src, board, this->color, MoveDirection::Up);
	pos.insert(pos.end(), upward.begin(), upward.end());

	vector<Position> downward = linearMove(src, board, this->color, MoveDirection::Down);
	pos.insert(pos.end(), downward.begin(), downward.end());

	vector<Position> leftward = linearMove(src, board, this->color, MoveDirection::Left);
	pos.insert(pos.end(), leftward.begin(), leftward.end());

	vector<Position> rightward = linearMove(src, board, this->color, MoveDirection::Right);
	pos.insert(pos.end(), rightward.begin(), rightward.end());

	vector<Position> upleft = linearMove(src, board, this->color, MoveDirection::UpLeft);
	pos.insert(pos.end(), upleft.begin(), upleft.end());

	vector<Position> upright = linearMove(src, board, this->color, MoveDirection::UpRight);
	pos.insert(pos.end(), upright.begin(), upright.end());

	vector<Position> downleft = linearMove(src, board, this->color, MoveDirection::DownLeft);
	pos.insert(pos.end(), downleft.begin(), downleft.end());

	vector<Position> downright = linearMove(src, board, this->color, MoveDirection::DownRight);
	pos.insert(pos.end(), downright.begin(), downright.end());

	return pos;
}

//===================================================
// King
//===================================================

void King::setRooksPosition(const Position& lRook, const Position& rRook) {
	// Only connects once
	if (this->leftRook.isNotNull() == true || this->rightRook.isNotNull() == true) {
		return;
	}
	this->leftRook = lRook;
	this->rightRook = rRook;
}

Position King::getLeftRook() const {
	return this->leftRook;
}

Position King::getRightRook() const {
	return this->rightRook;
}

void King::triggerOnFirstMove() {
	this->unCastlable();
}

Position King::getPosition()
{
	return this->kingPos;
}

void King::setPosition(const Position& p)
{
	this->kingPos = p;
}

vector<Position> King::canGo(const Position& src, const Board& board)
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
	pos = shortMove(src, board, this->color, moves);

	// Handle castling
	if (this->isCastlable() == false) {
		return pos;
	}

	// Note: If the king hasn't moved, all relative square that we get below will always
	// valid. Therefore, no need for checking nullptr.
	Position s_1;	// One square away
	Position s_2;	// Two square away
	Position s_3;	// Three square away


	// Left castling: R K B Q Ki
	// There's must be a Piece, which is Rook and castlable
	if (board.hasPiece(this->leftRook) == true &&
		board.getPiece(this->leftRook)->getPieceType() == PieceType::Rook &&
		((Rook*)board.getPiece(this->leftRook))->isCastlable() == true)
	{
		// 3 Squares on the left
		s_1 = src.getRelativePosition(0, -1);
		s_2 = src.getRelativePosition(0, -2);
		s_3 = src.getRelativePosition(0, -3);

		// The Path must be empty
		if (board.hasPiece(s_1) == false &&
			board.hasPiece(s_2) == false &&
			board.hasPiece(s_3) == false)
		{
			// Check squares that King go pass by is Dangerous
			if (isDangerousSquare(
				src,
				board,
				this->color
			) == false &&
				isDangerousSquare(
					s_1,
					board,
					this->color
				) == false &&
				isDangerousSquare(
					s_2,
					board,
					this->color
				) == false)
			{
				// End checking, add the postion if it satifies all conditions above
				Position castling = s_2;
				castling.setMoveType(PosInfo::CastlingLeft);
				pos.push_back(castling);
			}
		}
	}

	// Right castling: Ki B K R	
	// There's must be a Piece, which is Rook and castlable
	if (board.hasPiece(this->rightRook) == true &&
		board.getPiece(this->rightRook)->getPieceType() == PieceType::Rook &&
		((Rook*)board.getPiece(this->rightRook))->isCastlable() == true)
	{
		// 2 Squares on the Right
		s_1 = src.getRelativePosition(0, 1);
		s_2 = src.getRelativePosition(0, 2);

		// The Path must be empty
		if (board.hasPiece(s_1) == false &&
			board.hasPiece(s_2) == false)
		{
			// Check squares that King go pass by is Dangerous
			if (isDangerousSquare(
				src,
				board,
				this->color
			) == false &&
				isDangerousSquare(
					s_1,
					board,
					this->color
				) == false &&
				isDangerousSquare(
					s_2,
					board,
					this->color
				) == false)
			{
				// End checking, add the postion if it satifies all conditions above
				Position castling = s_2;
				castling.setMoveType(PosInfo::CastlingRight);
				pos.push_back(castling);
			}
		}
	}

	return pos;
}

Pawn::Pawn(const Pawn& p)
{
	this->color = p.color;
	this->pawnFirstMove = p.pawnFirstMove;
	this->isFirstMove = p.isFirstMove;
	this->type = p.type;
}

Bishop::Bishop(const Bishop& b)
{
	this->color = b.color;
	this->isFirstMove = b.isFirstMove;
	this->type = b.type;
}

Knight::Knight(const Knight& k)
{
	this->color = k.color;
	this->isFirstMove = k.isFirstMove;
	this->type = k.type;
}

Queen::Queen(const Queen& q)
{
	this->color = q.color;
	this->isFirstMove = q.isFirstMove;
	this->type = q.type;
}

Rook::Rook(const Rook& r)
{
	this->color = r.color;
	this->isFirstMove = r.isFirstMove;
	this->type = r.type;
	this->setCastlable(r.isCastlable());
}

King::King(const King& ki)
{
	this->color = ki.color;
	this->isFirstMove = ki.isFirstMove;
	this->type = ki.type;
	this->setCastlable(ki.isCastlable());

	this->leftRook = ki.leftRook;
	this->rightRook = ki.rightRook;

	this->kingPos = ki.kingPos;
}

Piece* Pawn::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new Pawn(*(dynamic_cast<Pawn*>(p)));
	return newPiece;
}

Piece* Bishop::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new Bishop(*(dynamic_cast<Bishop*>(p)));
	return newPiece;
}

Piece* Queen::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new Queen(*(dynamic_cast<Queen*>(p)));
	return newPiece;
}

Piece* Knight::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new Knight(*(dynamic_cast<Knight*>(p)));
	return newPiece;
}

Piece* Rook::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new Rook(*(dynamic_cast<Rook*>(p)));
	return newPiece;
}

Piece* King::deepCopyPiece(Piece* p)
{
	Piece* newPiece = new King(*(dynamic_cast<King*>(p)));
	return newPiece;
}