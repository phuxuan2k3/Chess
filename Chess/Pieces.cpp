#include "Pieces.h"


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
	const Board* broad = this->getBoard();
	Square* squareToMove = nullptr;

	vector<Position> pos;

	int range = 0;

	// upward
	while (true) {
		range += 1;
		squareToMove = this->standOn->getRelativeSquare(range, 0);
		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != this->getPieceColor()) {
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

	// downward
	while (true) {
		range -= 1;
		squareToMove = this->standOn->getRelativeSquare(range, 0);
		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// It's Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != this->getPieceColor()) {
				pos.push_back(squareToMove->getPosition());
			}
			break;
		}
		pos.push_back(squareToMove->getPosition());
	}

	// rightward
	while (true) {
		range += 1;
		squareToMove = this->standOn->getRelativeSquare(0, range);
		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// It's Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != this->getPieceColor()) {
				pos.push_back(squareToMove->getPosition());
			}
			break;
		}
		pos.push_back(squareToMove->getPosition());
	}

	// leftward
	while (true) {
		range -= 1;
		squareToMove = this->standOn->getRelativeSquare(0, range);
		// If it's out of range
		if (squareToMove == nullptr) {
			break;
		}
		// If it's blocked by a Piece
		if (squareToMove->isEmpty() == false) {
			// It's Enemy Piece
			if (squareToMove->getPiece()->getPieceColor() != this->getPieceColor()) {
				pos.push_back(squareToMove->getPosition());
			}
			break;
		}
		pos.push_back(squareToMove->getPosition());
	}
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

vector<Position> Knight::canGo()
{
	vector<Position> pos;

	//left-top
	int i = this->pos.i - 1;
	int j = this->pos.j - 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}
	i = this->pos.i - 2;
	j = this->pos.j - 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//left-bottom
	i = this->pos.i + 1;
	j = this->pos.j - 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i + 2;
	j = this->pos.j - 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//right-top
	i = this->pos.i - 1;
	j = this->pos.j + 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i - 2;
	j = this->pos.j + 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//right-bottom
	i = this->pos.i + 1;
	j = this->pos.j + 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i + 2;
	j = this->pos.j + 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board.board[i][j].piece == nullptr) || (board.board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}
	return pos;
}

//===================================================
// Bishop
//===================================================

vector<Position> Bishop::canGo()
{
	vector<Position> pos;

	//left-top
	int i = this->pos.i - 1;
	int j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i--;
		j--;
	}

	//left-bottom
	i = this->pos.i + 1;
	j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i++;
		j--;
	}

	//right-top
	i = this->pos.i - 1;
	j = this->pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i--;
		j++;
	}

	//right-bottom
	i = this->pos.i + 1;
	j = this->pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i++;
		j++;
	}
	return pos;
}

//===================================================
// Queen
//===================================================

vector<Position> Queen::canGo()
{
	vector<Position> pos;

	//upward
	int i = this->pos.i - 1;
	int j = this->pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i--;
	}

	//downward
	i = this->pos.i + 1;
	j = this->pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i++;
	}

	//rightward
	i = this->pos.i;
	j = this->pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		j++;
	}

	//leftward
	i = this->pos.i;
	j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		j--;
	}

	//left-top
	i = this->pos.i - 1;
	j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i--;
		j--;
	}

	//left-bottom
	i = this->pos.i + 1;
	j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i++;
		j--;
	}

	//right-top
	i = this->pos.i - 1;
	j = this->pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i--;
		j++;
	}

	//right-bottom
	i = this->pos.i + 1;
	j = this->pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board.board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		i++;
		j++;
	}
	return pos;
}

//===================================================
// King
//===================================================

vector<Position> King::canGo()
{
	vector<Position> pos;
	pos.push_back(Position(this->pos.i - 1, this->pos.j - 1));
	pos.push_back(Position(this->pos.i - 1, this->pos.j));
	pos.push_back(Position(this->pos.i - 1, this->pos.j + 1));
	pos.push_back(Position(this->pos.i, this->pos.j + 1));
	pos.push_back(Position(this->pos.i + 1, this->pos.j + 1));
	pos.push_back(Position(this->pos.i + 1, this->pos.j));
	pos.push_back(Position(this->pos.i + 1, this->pos.j - 1));
	pos.push_back(Position(this->pos.i, this->pos.j - 1));

	for (int k = pos.size() - 1; k >= 0; k--) {
		if ((Position::isOutOfRange(pos[k].i, pos[k].j) == true ||
			GameHandle::isDangerousSquare(board, pos[k], this->color) == true ||
			(board.board[pos[k].i][pos[k].j].piece != nullptr &&
				board.board[pos[k].i][pos[k].j].piece->color == this->color)))
		{
			pos.erase(pos.begin() + k);
		}
	}

	//nhap thanh phai
	Rook* rightRook = dynamic_cast<Rook*> (GameState::getInstance()->pieces[this->id + 3]);
	if (this->isFirstMove == true &&
		rightRook != nullptr &&
		rightRook->isFirstMove == true &&
		board.board[this->pos.i][this->pos.j + 1].piece == nullptr &&
		board.board[this->pos.i][this->pos.j + 2].piece == nullptr &&
		GameHandle::isDangerousSquare(board, this->pos, this->color) == false &&
		GameHandle::isDangerousSquare(board, Position(this->pos.i, this->pos.j + 1), this->color) == false &&
		GameHandle::isDangerousSquare(board, Position(this->pos.i, this->pos.j + 2), this->color) == false)
	{
		pos.push_back(Position(this->pos.i, this->pos.j + 2));
	}

	//nhap thanh trai
	Rook* leftRook = dynamic_cast<Rook*> (GameState::getInstance()->pieces[this->id - 4]);
	if (this->isFirstMove == true &&
		leftRook != nullptr &&
		leftRook->isFirstMove == true &&
		board.board[this->pos.i][this->pos.j - 1].piece == nullptr &&
		board.board[this->pos.i][this->pos.j - 2].piece == nullptr &&
		board.board[this->pos.i][this->pos.j - 3].piece == nullptr &&
		GameHandle::isDangerousSquare(board, this->pos, this->color) == false &&
		GameHandle::isDangerousSquare(board, Position(this->pos.i, this->pos.j - 1), this->color) == false &&
		GameHandle::isDangerousSquare(board, Position(this->pos.i, this->pos.j - 2), this->color) == false)
	{
		pos.push_back(Position(this->pos.i, this->pos.j - 2));
	}
	return pos;
}

void King::move(const Position& dest)
{
	Piece::move(dest);
	this->isFirstMove = false;
}
