#include "Chess.h"
#include <iostream>

using namespace std;

Piece* Manager::lastPieceChoosen = nullptr; 
bool Manager::enPassantBlack = false; 
bool Manager::enPassantWhite = false;




Position::Position()
{
	this->i = 0;
	this->j = 0;
}

Position::Position(const int& i, const int& j)
{
	this->i = i;
	this->j = j;
}

bool Position::operator== (const Position& pos)
{
	return this->i == pos.i && this->j == pos.j;
}

bool Position::isOutOfRange(const int& i, const int& j)
{
	if (i < 0 || j < 0 || i>7 || j>7)
	{
		return true;
	}
	return false;
}

Piece::Piece()
{
	this->id = 0;
	this->color = true;
}

Piece::Piece(bool color, Position pos, int id)
{
	this->color = color;
	this->pos = pos;
	this->id = id;
}

Pawn::Pawn(bool color, Position pos, int id) :Piece(color, pos, id)
{
}

Knight::Knight(bool color, Position pos, int id) : Piece(color, pos, id)
{
}

Bishop::Bishop(bool color, Position pos, int id) : Piece(color, pos, id)
{
}

Queen::Queen(bool color, Position pos, int id) : Piece(color, pos, id)
{
}

King::King(bool color, Position pos, int id) : Piece(color, pos, id)
{
}

Rook::Rook(bool color, Position pos, int id) : Piece(color, pos, id)
{
}

void Piece::move(const int& i, const int& j)
{	
	this->pos.i = i;
	this->pos.j = j;
	this->color == 1 ? Manager::enPassantWhite = false : Manager::enPassantBlack = false;
}

Piece::~Piece()
{
}

void Pawn::move(const int& i, const int& j)
{
	if (std::abs(i - this->pos.i) == 2 && this->isFirstMove == true) {
		this->color == 1 ? Manager::enPassantBlack = true : Manager::enPassantWhite = true;
	}
	this->pos.i = i;
	this->pos.j = j;
	this->isFirstMove = false;
	this->color == 1 ? Manager::enPassantWhite = false : Manager::enPassantBlack = false;
	Manager::lastPieceChoosen = this;
}

vector<Position> Pawn::canGo(Square board[8][8])
{
	vector<Position> pos;
	if (this->color == true)
	{
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j) == false && board[this->pos.i - 1][this->pos.j].piece == nullptr)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j));
			if (this->isFirstMove == true && Position::isOutOfRange(this->pos.i - 2, this->pos.j) == false && board[this->pos.i - 2][this->pos.j].piece == nullptr)
			{
				pos.push_back(Position(this->pos.i - 2, this->pos.j));
			}
		}
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j - 1) == false && board[this->pos.i - 1][this->pos.j - 1].piece != nullptr && board[this->pos.i - 1][this->pos.j - 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j - 1));
		}
		if (Position::isOutOfRange(this->pos.i - 1, this->pos.j + 1) == false && board[this->pos.i - 1][this->pos.j + 1].piece != nullptr && board[this->pos.i - 1][this->pos.j + 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i - 1, this->pos.j + 1));
		}
		if (Position::isOutOfRange(this->pos.i, this->pos.j - 1) == false && dynamic_cast<Pawn*>(board[this->pos.i][this->pos.j-1].piece) && Manager::lastPieceChoosen == board[this->pos.i][this->pos.j - 1].piece && Manager::enPassantWhite == true) {
			pos.push_back(Position(this->pos.i - 1, this->pos.j - 1));
		}
		if (Position::isOutOfRange(this->pos.i, this->pos.j + 1) == false && dynamic_cast<Pawn*>(board[this->pos.i][this->pos.j + 1].piece) && Manager::lastPieceChoosen == board[this->pos.i][this->pos.j + 1].piece && Manager::enPassantWhite == true) {
			pos.push_back(Position(this->pos.i - 1, this->pos.j + 1));
		}
	}
	else
	{
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j) == false && board[this->pos.i + 1][this->pos.j].piece == nullptr)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j));
			if (this->isFirstMove == true && Position::isOutOfRange(this->pos.i + 2, this->pos.j) == false && board[this->pos.i + 2][this->pos.j].piece == nullptr)
			{
				pos.push_back(Position(this->pos.i + 2, this->pos.j));
			}
		}
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j + 1) == false && board[this->pos.i + 1][this->pos.j + 1].piece != nullptr && board[this->pos.i + 1][this->pos.j + 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j + 1));
		}
		if (Position::isOutOfRange(this->pos.i + 1, this->pos.j - 1) == false && board[this->pos.i + 1][this->pos.j - 1].piece != nullptr && board[this->pos.i + 1][this->pos.j - 1].piece->color != this->color)
		{
			pos.push_back(Position(this->pos.i + 1, this->pos.j - 1));
		}
		if (Position::isOutOfRange(this->pos.i, this->pos.j - 1) == false && dynamic_cast<Pawn*>(board[this->pos.i][this->pos.j - 1].piece) && Manager::lastPieceChoosen == board[this->pos.i][this->pos.j - 1].piece && Manager::enPassantBlack == true) {
			pos.push_back(Position(this->pos.i + 1, this->pos.j - 1));
		}
		if (Position::isOutOfRange(this->pos.i, this->pos.j + 1) == false && dynamic_cast<Pawn*>(board[this->pos.i][this->pos.j + 1].piece) && Manager::lastPieceChoosen == board[this->pos.i][this->pos.j + 1].piece && Manager::enPassantBlack == true) {
			pos.push_back(Position(this->pos.i + 1, this->pos.j + 1));
		}
	}
	return pos;
}

Pawn::~Pawn()
{
}

vector<Position> Rook::canGo(Square board[8][8])
{
	vector<Position> pos;

	//upward
	int i = this->pos.i - 1;
	int j = this->pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
			{
				pos.push_back(Position(i, j));
			}
			break;
		}
		j--;
	}
	return pos;
}

void Rook::move(const int& i, const int& j)
{
	this->pos.i = i;
	this->pos.j = j;
	this->isFirstMove = false;
	this->color == 1 ? Manager::enPassantWhite = false : Manager::enPassantBlack = false;
}

vector<Position> Knight::canGo(Square board[8][8])
{
	vector<Position> pos;

	//left-top
	int i = this->pos.i - 1;
	int j = this->pos.j - 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}
	i = this->pos.i - 2;
	j = this->pos.j - 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//left-bottom
	i = this->pos.i + 1;
	j = this->pos.j - 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i + 2;
	j = this->pos.j - 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//right-top
	i = this->pos.i - 1;
	j = this->pos.j + 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i - 2;
	j = this->pos.j + 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	//right-bottom
	i = this->pos.i + 1;
	j = this->pos.j + 2;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}

	i = this->pos.i + 2;
	j = this->pos.j + 1;
	if (Position::isOutOfRange(i, j) == false)
	{
		if ((board[i][j].piece == nullptr) || (board[i][j].piece->color != this->color))
		{
			pos.push_back(Position(i, j));
		}
	}
	return pos;
}

vector<Position> Bishop::canGo(Square board[8][8])
{
	vector<Position> pos;

	//left-top
	int i = this->pos.i - 1;
	int j = this->pos.j - 1;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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

vector<Position> Queen::canGo(Square board[8][8])
{
	vector<Position> pos;

	//upward
	int i = this->pos.i - 1;
	int j = this->pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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
		if (board[i][j].piece == nullptr)
		{
			pos.push_back(Position(i, j));
		}
		else
		{
			if (board[i][j].piece->color != this->color)
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

vector<Position> King::canGo(Square board[8][8])
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
		if ((Position::isOutOfRange(pos[k].i, pos[k].j) == true || Manager::isDangerousSquare(board, pos[k], this->color) == true || (board[pos[k].i][pos[k].j].piece != nullptr && board[pos[k].i][pos[k].j].piece->color == this->color)))
		{
			pos.erase(pos.begin() + k);
		}
	}

	//nhap thanh phai
	Rook* rightRook = dynamic_cast<Rook*> (Manager::pieces[this->id + 3]);
	if (this->isFirstMove == true && rightRook != nullptr && rightRook->isFirstMove == true && board[this->pos.i][this->pos.j + 1].piece == nullptr && board[this->pos.i][this->pos.j + 2].piece == nullptr && Manager::isDangerousSquare(board, this->pos, this->color) == false && Manager::isDangerousSquare(board, Position(this->pos.i, this->pos.j + 1), this->color) == false && Manager::isDangerousSquare(board, Position(this->pos.i, this->pos.j + 2), this->color) == false)
	{
		pos.push_back(Position(this->pos.i, this->pos.j + 2));
	}

	//nhap thanh trai
	Rook* leftRook = dynamic_cast<Rook*> (Manager::pieces[this->id - 4]);
	if (this->isFirstMove == true && leftRook != nullptr && leftRook->isFirstMove == true && board[this->pos.i][this->pos.j - 1].piece == nullptr && board[this->pos.i][this->pos.j - 2].piece == nullptr && board[this->pos.i][this->pos.j - 3].piece == nullptr && Manager::isDangerousSquare(board, this->pos, this->color) == false && Manager::isDangerousSquare(board, Position(this->pos.i, this->pos.j - 1), this->color) == false && Manager::isDangerousSquare(board, Position(this->pos.i, this->pos.j - 2), this->color) == false)
	{
		pos.push_back(Position(this->pos.i, this->pos.j - 2));
	}
	return pos;
}

void King::move(const int& i, const int& j)
{
	this->pos.i = i;
	this->pos.j = j;
	this->isFirstMove = false;
	this->color == 1 ? Manager::enPassantWhite = false : Manager::enPassantBlack = false;
}

Square::Square()
{
	this->width = 100;
	this->height = 100;
	this->piece = nullptr;
	this->coordinate = sf::Vector2f(0, 0);
}

void Square::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

string Square::getPieceName()
{
	if (Pawn* p = dynamic_cast<Pawn*>(this->piece))
	{
		if (p->color == 1)
		{
			return "pt";
		}
		return "p";
	}
	else if (Bishop* p = dynamic_cast<Bishop*>(this->piece))
	{
		if (p->color == 1)
		{
			return "bt";
		}
		return "b";
	}
	else if (Knight* p = dynamic_cast<Knight*>(this->piece))
	{
		if (p->color == 1)
		{
			return "knt";
		}
		return "kn";
	}
	else if (Rook* p = dynamic_cast<Rook*>(this->piece))
	{
		if (p->color == 1)
		{
			return "rt";
		}
		return "r";
	}
	else if (Queen* p = dynamic_cast<Queen*>(this->piece))
	{
		if (p->color == 1)
		{
			return "qt";
		}
		return "q";
	}
	else if (King* p = dynamic_cast<King*>(this->piece))
	{
		if (p->color == 1)
		{
			return "kit";
		}
		return "ki";
	}
	return "";
}

void Square::draw(sf::RenderWindow& window)
{
	//draw background square
	sf::RectangleShape square(sf::Vector2f(100, 100));
	square.setPosition(this->coordinate);
	square.setFillColor(this->color == true ? sf::Color(255, 255, 178) : sf::Color(85, 46, 20, 255));
	window.draw(square);

	//draw sprite piece
	if (this->piece != nullptr)
	{
		sf::Texture texture;
		texture.loadFromFile(this->getPieceName() + ".png", sf::IntRect(0, 0, 100, 100));
		texture.setSmooth(true);

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(this->coordinate);
		if (this->piece->color == true)
		{
			sprite.setColor(sf::Color(255, 255, 75));
		}
		window.draw(sprite);
	}
}

void Square::drawCanGo(sf::RenderWindow& window)
{
	sf::CircleShape square(20);
	square.setPosition(this->coordinate.x + 30, this->coordinate.y + 30);
	square.setFillColor(sf::Color(255, 0, 0));
	/*square.setOutlineColor(sf::Color(255, 0, 0));
	square.setOutlineThickness(50);*/
	window.draw(square);
}

void Board::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

Board::Board()
{
	this->width = 800;
	this->height = 800;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j].piece = nullptr;
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
			{
				this->board[i][j].color = true;
			}
			else
			{
				this->board[i][j].color = false;
			}
			this->board[i][j].coordinate = sf::Vector2f(j * 100, i * 100);
		}
	}

	//black
	this->board[0][0].piece = new Rook(false, Position(0, 0), 0);
	this->board[0][1].piece = new Knight(false, Position(0, 1), 1);
	this->board[0][2].piece = new Bishop(false, Position(0, 2), 2);
	this->board[0][3].piece = new Queen(false, Position(0, 3), 3);
	this->board[0][4].piece = new King(false, Position(0, 4), 4);
	this->board[0][5].piece = new Bishop(false, Position(0, 5), 5);
	this->board[0][6].piece = new Knight(false, Position(0, 6), 6);
	this->board[0][7].piece = new Rook(false, Position(0, 7), 7);

	for (int j = 0; j < 8; j++)
	{
		this->board[1][j].piece = new Pawn(false, Position(1, j), j + 8);
	}

	//white
	this->board[7][0].piece = new Rook(true, Position(7, 0), 24);
	this->board[7][1].piece = new Knight(true, Position(7, 1), 25);
	this->board[7][2].piece = new Bishop(true, Position(7, 2), 26);
	this->board[7][3].piece = new Queen(true, Position(7, 3), 27);
	this->board[7][4].piece = new King(true, Position(7, 4), 28);
	this->board[7][5].piece = new Bishop(true, Position(7, 5), 29);
	this->board[7][6].piece = new Knight(true, Position(7, 6), 30);
	this->board[7][7].piece = new Rook(true, Position(7, 7), 31);
	for (int j = 0; j < 8; j++)
	{
		this->board[6][j].piece = new Pawn(true, Position(6, j), j + 16);
	}

	for (int j = 0; j < 8; j++)
	{
		Manager::pieces.push_back(this->board[0][j].piece);
	}
	for (int j = 0; j < 8; j++)
	{
		Manager::pieces.push_back(this->board[1][j].piece);
	}
	for (int j = 0; j < 8; j++)
	{
		Manager::pieces.push_back(this->board[6][j].piece);
	}
	for (int j = 0; j < 8; j++)
	{
		Manager::pieces.push_back(this->board[7][j].piece);
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//	this->board[i][j].setSize(this->width / 8, this->height / 8);
			this->board[i][j].draw(window);
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete this->board[i][j].piece;
		}
	}
}

bool Manager::isDangerousSquare(Square board[8][8], Position pos, bool color)
{
	//top
	int i = pos.i - 1;
	int j = pos.j;
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
				if ((namePiece.find_first_of("r", 0) != std::string::npos) || (namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i - 2))
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
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
				if ((namePiece.find_first_of("r", 0) != std::string::npos) || (namePiece.find_first_of("q", 0) != std::string::npos) || (namePiece.find_first_of("ki", 0) != std::string::npos && i == pos.i + 2))
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
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
	if (Position::isOutOfRange(i, j) == false && board[i][j].piece != nullptr && board[i][j].piece->color != color && color == true && board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
	if (Position::isOutOfRange(i, j) == false && board[i][j].piece != nullptr && board[i][j].piece->color != color && color == true && board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
	if (Position::isOutOfRange(i, j) == false && board[i][j].piece != nullptr && board[i][j].piece->color != color && color == false && board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
	if (Position::isOutOfRange(i, j) == false && board[i][j].piece != nullptr && board[i][j].piece->color != color && color == false && board[i][j].getPieceName().find_first_of("p", 0) != std::string::npos)
	{
		return true;
	}
	while (Position::isOutOfRange(i, j) == false)
	{
		if (board[i][j].piece != nullptr)
		{
			if (board[i][j].piece->color != color)
			{
				string namePiece = board[i][j].getPieceName();
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
		if (Position::isOutOfRange(k.i, k.j) == false && board[k.i][k.j].piece != nullptr && board[k.i][k.j].piece->color != color && board[k.i][k.j].getPieceName().find_first_of("kn", 0) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

Manager::Manager()
{
	this->windowWidthScale = 1;
	this->windowHeightScale = 1;
	this->window.create(sf::VideoMode(950, 800), "Phú Xuân Chess!");
	this->b.draw(this->window);
	this->window.display();
	this->turn = 1;
	this->isPieceChoose = false;
}

Position Manager::coordinateToPosition(sf::Vector2i coor)
{
	int j = coor.x / 100;
	int i = coor.y / 100;
	return Position(i, j);
}

vector<Piece*> Manager::pieces;

void Manager::play()
{
	vector<Position> canGo; // luu lai cac o co the di cua con co duoc chon
	Piece* pieceChoosen = nullptr; // luu lai con co duoc chon

	while (this->window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				this->windowWidthScale = this->window.getSize().x * 1.0f / 950;
				this->windowHeightScale = this->window.getSize().y * 1.0f / 800;
				this->window.clear();
				this->b.draw(this->window);
				this->window.display();
			}
			//xu ly su kien nhap chuot vao quan co
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(this->window).x * 1.0f / this->windowWidthScale, sf::Mouse::getPosition(this->window).y * 1.0f / this->windowHeightScale);
				if (mousePosition.x <= 800)
				{
					Position vt = this->coordinateToPosition(mousePosition);
					//neu chua chon mot quan co truoc do thi hien len duong di cua quan co duoc chon  va phai den turn
					if (this->isPieceChoose == false && this->b.board[vt.i][vt.j].piece != nullptr && this->turn == this->b.board[vt.i][vt.j].piece->color)
					{
						if ((this->turn == true && (((Manager::isDangerousSquare(this->b.board, Position(this->pieces[28]->pos.i, this->pieces[28]->pos.j), this->turn) == true && dynamic_cast<King*>(this->b.board[vt.i][vt.j].piece)) || Manager::isDangerousSquare(this->b.board, Position(this->pieces[28]->pos.i, this->pieces[28]->pos.j), this->turn) == false))) || (this->turn == false && (((Manager::isDangerousSquare(this->b.board, Position(this->pieces[4]->pos.i, this->pieces[4]->pos.j), this->turn) == true && dynamic_cast<King*>(this->b.board[vt.i][vt.j].piece)) || Manager::isDangerousSquare(this->b.board, Position(this->pieces[4]->pos.i, this->pieces[4]->pos.j), this->turn) == false))))
						{
							this->isPieceChoose = true;
							this->window.clear();
							this->b.draw(this->window);

							pieceChoosen = this->b.board[vt.i][vt.j].piece;
							canGo = this->b.board[vt.i][vt.j].piece->canGo(this->b.board);
							for (auto k : canGo)
							{
								this->b.board[k.i][k.j].drawCanGo(this->window);
							}
							this->window.display();
						}
					}
					//neu da chon mot quan co truoc do thi thuc hien viec di chuyen
					else if (this->isPieceChoose == true)
					{
						for (auto k : canGo)
						{
							//o duoc chon de di chuyen la hop le
							if (k == vt)
							{
								//neu co con co thi xoa con co do
								if (this->b.board[k.i][k.j].piece != nullptr)
								{
									int id = this->b.board[k.i][k.j].piece->id;
									delete Manager::pieces[id];
									Manager::pieces[id] = nullptr;
									this->b.board[k.i][k.j].piece = nullptr;
								}
								else { // Phần xóa quân cờ đối với trường hợp bắt tốt qua đường
									if (dynamic_cast<Pawn*>(pieceChoosen) && pieceChoosen->pos.j != k.j) {
										if (pieceChoosen->color == 1 && enPassantWhite == true) {
											int id = this->b.board[k.i + 1][k.j].piece->id; // Nếu là lượt cờ trắng thì bên dưới vị trí chọn là tốt cần xóa
											delete Manager::pieces[id];
											Manager::pieces[id] = nullptr;
											this->b.board[k.i + 1][k.j].piece = nullptr;
										}
										if (pieceChoosen->color == 0 && enPassantBlack == true) {
											int id = this->b.board[k.i - 1][k.j].piece->id; // Nếu là lượt cờ đen thì trên vị trí chon là tốt cần xóa
											delete Manager::pieces[id];
											Manager::pieces[id] = nullptr;
											this->b.board[k.i - 1][k.j].piece = nullptr;
										}
									}
								}


								//gan con co qua o moi
								this->b.board[k.i][k.j].piece = pieceChoosen;
								this->b.board[pieceChoosen->pos.i][pieceChoosen->pos.j].piece = nullptr;
								//nhap thanh phai
								if (dynamic_cast<King*>(pieceChoosen) != nullptr)
								{
									if (k.j == pieceChoosen->pos.j + 2)
									{
										Piece* rightRook = Manager::pieces[pieceChoosen->id + 3];
										this->b.board[k.i][k.j - 1].piece = rightRook;
										this->b.board[rightRook->pos.i][rightRook->pos.j].piece = nullptr;
										rightRook->move(k.i, k.j - 1);
									}
									else if (k.j == pieceChoosen->pos.j - 2)
									{
										Piece* leftRook = Manager::pieces[pieceChoosen->id - 4];
										this->b.board[k.i][k.j + 1].piece = leftRook;
										this->b.board[leftRook->pos.i][leftRook->pos.j].piece = nullptr;
										leftRook->move(k.i, k.j + 1);
									}
								}
								this->b.board[k.i][k.j].piece->move(k.i, k.j);

								this->turn = !this->turn;
								break;
							}
						}
						this->isPieceChoose = false;
						this->window.clear();
						this->b.draw(this->window);
						this->window.display();
					}
				}
			}
		}
	}
}