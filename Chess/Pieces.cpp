#include "Pieces.h"


Pawn::Pawn(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::Pawn;
}

Knight::Knight(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::Knight;
}

Bishop::Bishop(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::Bishop;
}

Rook::Rook(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::Rook;
}

Queen::Queen(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::Queen;
}

King::King(PieceColor color, Position pos, int id) : Piece(color, pos, id)
{
	this->type = PieceName::King;
}


//===================================================
// Pawn
//===================================================

void Pawn::move(const Position& pos)
{
	Piece::move(pos);
	this->isFirstMove = false;
}

vector<Position> Pawn::canGo(const Board& board)
{
	// Inverse coefficient - inv
	int inv = 1;
	vector<Position> pos;

	if (this->color == PieceColor::White) {
		inv = -1;	// White will go upward
	}
	else {
		inv = 1;	// Black will go downward
	}

	

	if (Position::isOutOfRange(this->pos.i - 1, this->pos.j) == false && board.board[this->pos.i - 1][this->pos.j].piece == nullptr)
	{
		pos.push_back(Position(this->pos.i - 1, this->pos.j));
		if (this->isFirstMove == true && Position::isOutOfRange(this->pos.i - 2, this->pos.j) == false && board.board[this->pos.i - 2][this->pos.j].piece == nullptr)
		{
			pos.push_back(Position(this->pos.i - 2, this->pos.j));
		}
	}
	if (Position::isOutOfRange(this->pos.i - 1, this->pos.j - 1) == false && board.board[this->pos.i - 1][this->pos.j - 1].piece != nullptr && board.board[this->pos.i - 1][this->pos.j - 1].piece->color != this->color)
	{
		pos.push_back(Position(this->pos.i - 1, this->pos.j - 1));
	}
	if (Position::isOutOfRange(this->pos.i - 1, this->pos.j + 1) == false && board.board[this->pos.i - 1][this->pos.j + 1].piece != nullptr && board.board[this->pos.i - 1][this->pos.j + 1].piece->color != this->color)
	{
		pos.push_back(Position(this->pos.i - 1, this->pos.j + 1));
	}


	if (this->color == true)
	{
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j) == false && board.board[this->pos.i - 1][this->pos.j].piece == nullptr)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j));
			if (this->isFirstMove == true && Position::isOutOfRange(this->pos.i - 2, this->pos.j) == false && board.board[this->pos.i - 2][this->pos.j].piece == nullptr)
			{
				pos.push_back(Position(this->pos.i - 2, this->pos.j));
			}
		}
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j - 1) == false && board.board[this->pos.i - 1][this->pos.j - 1].piece != nullptr && board.board[this->pos.i - 1][this->pos.j - 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j - 1));
		}
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j + 1) == false && board.board[this->pos.i - 1][this->pos.j + 1].piece != nullptr && board.board[this->pos.i - 1][this->pos.j + 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j + 1));
		}
	}
	else
	{
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j) == false && board.board[this->pos.i + 1][this->pos.j].piece == nullptr)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j));
			if (this->isFirstMove == true && Position::isOutOfRange(this->pos.i + 2, this->pos.j) == false && board.board[this->pos.i + 2][this->pos.j].piece == nullptr)
			{
				pos.push_back(Position(this->pos.i + 2, this->pos.j));
			}
		}
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j + 1) == false && board.board[this->pos.i + 1][this->pos.j + 1].piece != nullptr && board.board[this->pos.i + 1][this->pos.j + 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j + 1));
		}
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j - 1) == false && board.board[this->pos.i + 1][this->pos.j - 1].piece != nullptr && board.board[this->pos.i + 1][this->pos.j - 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j - 1));
		}
	}
	return pos;
}

Pawn::~Pawn()
{
}

//===================================================
// Rook
//===================================================

vector<Position> Rook::canGo(const Board& board)
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
	return pos;
}

void Rook::move(const Position& pos)
{
	Piece::move(pos);
	this->isFirstMove = false;
}

//===================================================
// Knight
//===================================================

vector<Position> Knight::canGo(const Board& board)
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

vector<Position> Bishop::canGo(const Board& board)
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

vector<Position> Queen::canGo(const Board& board)
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

vector<Position> King::canGo(const Board& board)
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

void King::move(const Position& pos)
{
	Piece::move(pos);
	this->isFirstMove = false;
}
