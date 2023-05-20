#include "Render.h"



//===================================================
// RenderSquare
//===================================================

RenderSquare::RenderSquare(ThemeColor color, const sf::Vector2f& coordinate)
{
	this->width = DEFAULT_SIZE;
	this->height = DEFAULT_SIZE;
	this->coordinate = coordinate;
	this->themeColor = color;
	this->pieceType = PieceName::None;
	this->pieceColor = PieceColor::None;
}

RenderSquare::RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, PieceName type, PieceColor pieceColor)
{
	this->width = DEFAULT_SIZE;
	this->height = DEFAULT_SIZE;
	this->coordinate = coordinate;
	this->themeColor = color;
	this->pieceType = type;
	this->pieceColor = pieceColor;
}

RenderSquare::RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, PieceName type, PieceColor pieceColor, float width, float height)
{
	this->width = width;
	this->height = height;
	this->coordinate = coordinate;
	this->themeColor = color;
	this->pieceType = type;
	this->pieceColor = pieceColor;
}

RenderSquare::~RenderSquare() 
{
}

void RenderSquare::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

void RenderSquare::setPiece(PieceName pieceType, PieceColor pieceColor) {
	this->pieceColor = pieceColor;
	this->pieceType = pieceType;
}


void RenderSquare::draw(sf::RenderWindow& window)
{
	// Draw background
	sf::RectangleShape square(sf::Vector2f(this->width, this->height));
	square.setPosition(this->coordinate);
	// Set color of background
	switch (themeColor)
	{
	case ThemeColor::Black:
		square.setFillColor(sf::Color(85, 46, 20, 255));	// 4 so????
		break;
	case ThemeColor::White:
		square.setFillColor(sf::Color(255, 255, 178));
		break;
	default:
		break;
	}
	window.draw(square);

	// Draw piece's sprite
	if (this->pieceType != PieceName::None &&
		this->pieceColor != PieceColor::None) 
	{
		sf::Texture texture;
		string spriteName = getSprite(this->pieceType, this->pieceColor);

		texture.loadFromFile(spriteName + ".png", sf::IntRect(0, 0, this->width, this->height));
		texture.setSmooth(true);
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(this->coordinate);
		if (this->pieceColor == PieceColor::White)
		{
			sprite.setColor(sf::Color(255, 255, 75));
		}
		window.draw(sprite);
	}
}

void RenderSquare::drawCanGo(sf::RenderWindow& window)
{
	sf::CircleShape square(20);
	square.setPosition(this->coordinate.x + 30, this->coordinate.y + 30);
	square.setFillColor(sf::Color(255, 0, 0));
	/*square.setOutlineColor(sf::Color(255, 0, 0));
	square.setOutlineThickness(50);*/
	window.draw(square);
}

//===================================================
// RenderBoard
//===================================================

RenderBoard::RenderBoard()
{
	// Will initialize RenderSquare associate with each Square inside
	// of the referenced Board
	this->squareMat = new RenderSquare * [8];
	for (int i = 0; i < 8; ++i) {
		this->squareMat[i] = new RenderSquare[8]{
			RenderSquare(
				(i + 0) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(0 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 1) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(1 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 2) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(2 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 3) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(3 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 4) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(4 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 5) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(5 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 6) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(6 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
			RenderSquare(
				(i + 7) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(7 * DEFAULT_SIZE, i * DEFAULT_SIZE)),
		};
	}

	this->width = DEFAULT_SIZE * 800;
	this->height = DEFAULT_SIZE * 800;

	this->board = nullptr;
}

void RenderBoard::setBoard(const Board* board) {
	this->board = board;
}

void RenderBoard::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

void RenderBoard::setPieces() {
	Piece* p;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			p = this->board->getPiece(i, j);
			if (p == nullptr) {
				this->squareMat[i][j].setPiece(PieceName::None, PieceColor::None);
			}
			else {
				this->squareMat[i][j].setPiece(p->getPieceName(), p->getPieceColor());
			}
		}
	}
}

void RenderBoard::draw(sf::RenderWindow& window)
{
	if (this->board == nullptr) {
		throw UninitializedException();
	}

	// Update Pieces before draw
	this->setPieces();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//	this->board[i][j].setSize(this->width / 8, this->height / 8);
			this->squareMat[i][j].draw(window);
		}
	}
}

void RenderBoard::drawCanGo(sf::RenderWindow& window, vector<Position> squares) {
	for (Position p : squares) {
		this->squareMat[p.get_i()][p.get_j()].drawCanGo(window);
	}
}

RenderBoard::~RenderBoard()
{
	for (int i = 0; i < 8; ++i) {
		delete[] this->squareMat[i];
	}
	delete[] this->squareMat;
}

//===================================================
// Window
//===================================================

RenderGame::RenderGame()
{
	this->state = State::NotSelected;
}

void RenderGame::setBoard(const Board* board) {
	this->b.setBoard(board);
}

State RenderGame::getState() const {
	return this->state;
}

void RenderGame::draw(sf::RenderWindow& window) {
	this->state = State::NotSelected;
	this->b.draw(window);
}

void RenderGame::drawCanGo(sf::RenderWindow& window, vector<Position> squares) {
	this->state = State::Selected;
	this->b.drawCanGo(window, squares);
}
