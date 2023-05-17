#include "Handle.h"


bool GameHandle::isDangerousSquare(const Board& board, Position pos, bool color)
{
	//top
	int i = pos.i - 1;
	int j = pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if (
					(namePiece.find_first_of("r", 0) != std::string::npos) ||
					(namePiece.find_first_of("q", 0) != std::string::npos) || 
					(namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i - 2)
					)
				{
					return true;
				}
			}
			break;
		}
		i--;
	}

	//bottom
	i = pos.i + 1;
	j = pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if (
					(namePiece.find_first_of("r", 0) != std::string::npos) ||
					(namePiece.find_first_of("q", 0) != std::string::npos) ||
					(namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i + 2)
					)
				{
					return true;
				}
			}
			break;
		}
		i++;
	}

	//left
	i = pos.i;
	j = pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("r", 0) != std::string::npos) || (namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && j == pos.j - 2))
				{
					return true;
				}
			}
			break;
		}
		j--;
	}

	//right
	i = pos.i;
	j = pos.j + 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("r", 0) != std::string::npos) || (namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && j == pos.j + 2))
				{
					return true;
				}
			}
			break;
		}
		j++;
	}

	//left-top
	i = pos.i - 1;
	j = pos.j - 1;
	if (Position::isOutOfRange(i, j) == false && board.board[i][j].piece != nullptr && board.board[i][j].piece->color != color && color == true && board.board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("b", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i - 2 && j == pos.j - 2))
				{
					return true;
				}
			}
			break;
		}
		i--;
		j--;
	}

	//right-top
	i = pos.i - 1;
	j = pos.j + 1;
	//if the diagon is the pawn which is diffrent color
	if (Position::isOutOfRange(i, j) == false && board.board[i][j].piece != nullptr && board.board[i][j].piece->color != color && color == true && board.board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("b", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i - 2 && j == pos.j + 2))
				{
					return true;
				}
			}
			break;
		}
		i--;
		j++;
	}

	//left-bottom
	i = pos.i + 1;
	j = pos.j - 1;
	//if the diagon is the pawn which is diffrent color
	if (Position::isOutOfRange(i, j) == false && board.board[i][j].piece != nullptr && board.board[i][j].piece->color != color && color == false && board.board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("b", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i + 2 && j == pos.j - 2))
				{
					return true;
				}
			}
			break;
		}
		i++;
		j--;
	}


	//right-bottom
	i = pos.i + 1;
	j = pos.j + 1;
	//if the diagon is the pawn which is diffrent color
	if (Position::isOutOfRange(i, j) == false && board.board[i][j].piece != nullptr && board.board[i][j].piece->color != color && color == false && board.board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board.board[i][j].piece != nullptr)
		{
			if (board.board[i][j].piece->color != color)
			{
				string namePiece = board.board[i][j].getPieceName();
				if ((namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("b", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i + 2 && j == pos.j + 2))
				{
					return true;
				}
			}
			break;
		}
		i++;
		j++;
	}

	//check knight
	vector<Position> knightPos;
	knightPos.push_back(Position(pos.i - 1, pos.j - 2));
	knightPos.push_back(Position(pos.i - 2, pos.j - 1));
	knightPos.push_back(Position(pos.i - 1, pos.j + 2));
	knightPos.push_back(Position(pos.i - 2, pos.j + 1));
	knightPos.push_back(Position(pos.i + 1, pos.j - 2));
	knightPos.push_back(Position(pos.i + 2, pos.j - 1));
	knightPos.push_back(Position(pos.i + 1, pos.j + 2));
	knightPos.push_back(Position(pos.i + 2, pos.j + 1));

	for (auto k : knightPos)
	{
		if (Position::isOutOfRange(k.i, k.j) == false && board.board[k.i][k.j].piece != nullptr && board.board[k.i][k.j].piece->color != color && board.board[k.i][k.j].getPieceName().find_first_of("kn", 0) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}