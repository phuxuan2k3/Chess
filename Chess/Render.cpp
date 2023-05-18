#include "Render.h"



//===================================================
// RenderSquare
//===================================================

RenderSquare::RenderSquare(ThemeColor color, const sf::Vector2f& coordinate, Square* associate)
{
	this->square = square;

	this->width = DEFAULT_SIZE;
	this->height = DEFAULT_SIZE;
	this->coordinate = coordinate;
	this->themeColor = color;
}

RenderSquare::~RenderSquare() 
{
}

void RenderSquare::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
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
	if (this->square->getPiece() != nullptr)
	{
		sf::Texture texture;
		texture.loadFromFile(this->square->getPieceName() + ".png", sf::IntRect(0, 0, this->width, this->height));
		texture.setSmooth(true);

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(this->coordinate);
		if (this->square->getPiece()->getPieceColor() == PieceColor::White)
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



RenderBoard::RenderBoard(const Board* associate)
{
	this->board = associate;

	// Will initialize RenderSquare associate with each Square inside
	// of the referenced Board
	this->squareMat = new RenderSquare * [8];
	for (int i = 0; i < 8; ++i) {
		this->squareMat[i] = new RenderSquare[8]{
			RenderSquare(
				(i + 0) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(0 * 100, i * 100),
				associate->getSquare(i, 0)),
			RenderSquare(
				(i + 1) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(1 * 100, i * 100),
				associate->getSquare(i, 1)),
			RenderSquare(
				(i + 2) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(2 * 100, i * 100),
				associate->getSquare(i, 2)),
			RenderSquare(
				(i + 3) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(3 * 100, i * 100),
				associate->getSquare(i, 3)),
			RenderSquare(
				(i + 4) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(4 * 100, i * 100),
				associate->getSquare(i, 4)),
			RenderSquare(
				(i + 5) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(5 * 100, i * 100),
				associate->getSquare(i, 5)),
			RenderSquare(
				(i + 6) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(6 * 100, i * 100),
				associate->getSquare(i, 6)),
			RenderSquare(
				(i + 7) % 2 == 0 ? ThemeColor::White : ThemeColor::Black,
				sf::Vector2f(7 * 100, i * 100),
				associate->getSquare(i, 7)),
		};
	}

	this->width = 800;
	this->height = 800;
}

void RenderBoard::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

void RenderBoard::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//	this->board[i][j].setSize(this->width / 8, this->height / 8);
			this->squareMat[i][j].draw(window);
		}
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
// Manager
//===================================================

Manager::Manager(const Board* board) : b(board)
{
	this->windowWidthScale = 1;
	this->windowHeightScale = 1;
	this->window.create(sf::VideoMode(950, 800), "");
	this->b.draw(this->window);
	this->window.display();
}

Position Manager::coordinateToPosition(sf::Vector2i coor)
{
	int j = coor.x / 100;
	int i = coor.y / 100;
	return Position(i, j);
}



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
				sf::Vector2i mousePosition = 
					sf::Vector2i(
						sf::Mouse::getPosition(this->window).x * 1.0f / this->windowWidthScale,
						sf::Mouse::getPosition(this->window).y * 1.0f / this->windowHeightScale
					);

				if (mousePosition.x <= 800)
				{
					Position vt = this->coordinateToPosition(mousePosition);
					//neu chua chon mot quan co truoc do thi hien len duong di cua quan co duoc chon  va phai den turn
					if (GameState::getInstance()->isPieceChoose == false &&
						this->b.squareMat[vt.i][vt.j].square->piece != nullptr &&
						GameState::getInstance()->turn == this->b.squareMat[vt.i][vt.j].square->piece->color)
					{
						if ((GameState::getInstance()->turn == true &&
							(((GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == true &&
								dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
								GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == false))) ||
							(GameState::getInstance()->turn == false &&
								(((GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == true &&
									dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
									GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == false)))
							)
						{
							GameState::getInstance()->isPieceChoose = true;
							this->window.clear();
							this->b.draw(this->window);

							pieceChoosen = this->b.Board.board[vt.i][vt.j].piece;
							canGo = this->b.Board.board[vt.i][vt.j].piece->canGo(this->b.Board);
							for (Position k : canGo)
							{
								this->b.squareMat[k.i][k.j].drawCanGo(this->window);
							}
							this->window.display();
						}
					}
					//neu da chon mot quan co truoc do thi thuc hien viec di chuyen
					else if (GameState::getInstance()->isPieceChoose == true)
					{
						for (auto k : canGo)
						{
							//o duoc chon de di chuyen la hop le
							if (k == vt)
							{
								//neu co con co thi xoa con co do
								if (this->b.Board.board[k.i][k.j].piece != nullptr)
								{
									int id = this->b.Board.board[k.i][k.j].piece->id;
									delete GameState::getInstance()->pieces[id];
									GameState::getInstance()->pieces[id] = nullptr;
									this->b.Board.board[k.i][k.j].piece = nullptr;
								}

								//gan con co qua o moi
								this->b.Board.board[k.i][k.j].piece = pieceChoosen;
								this->b.Board.board[pieceChoosen->pos.i][pieceChoosen->pos.j].piece = nullptr;
								//nhap thanh phai
								if (dynamic_cast<King*>(pieceChoosen) != nullptr)
								{
									if (k.j == pieceChoosen->pos.j + 2)
									{
										Piece* rightRook = GameState::getInstance()->pieces[pieceChoosen->id + 3];
										this->b.Board.board[k.i][k.j - 1].piece = rightRook;
										this->b.Board.board[rightRook->pos.i][rightRook->pos.j].piece = nullptr;
										rightRook->move(k.i, k.j - 1);
									}
									else if (k.j == pieceChoosen->pos.j - 2)
									{
										Piece* leftRook = GameState::getInstance()->pieces[pieceChoosen->id - 4];
										this->b.Board.board[k.i][k.j + 1].piece = leftRook;
										this->b.Board.board[leftRook->pos.i][leftRook->pos.j].piece = nullptr;
										leftRook->move(k.i, k.j + 1);
									}
								}
								this->b.Board.board[k.i][k.j].piece->move(k.i, k.j);

								GameState::getInstance()->turn = !GameState::getInstance()->turn;
								break;
							}
						}
						GameState::getInstance()->isPieceChoose = false;
						this->window.clear();
						this->b.draw(this->window);
						this->window.display();
					}
				}
			}
		}
	}
}