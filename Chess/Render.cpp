#include "Render.h"


RenderSquare::RenderSquare(bool color)
{
	this->square = square;

	this->width = 100;
	this->height = 100;
	this->coordinate = sf::Vector2f(0, 0);
	this->color = color;
}

RenderSquare::~RenderSquare() {

}

void RenderSquare::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

void RenderSquare::draw(sf::RenderWindow& window)
{
	//draw background square
	sf::RectangleShape square(sf::Vector2f(100, 100));
	square.setPosition(this->coordinate);
	square.setFillColor(this->color == true ? sf::Color(255, 255, 178) : sf::Color(85, 46, 20, 255));
	window.draw(square);

	//draw sprite piece
	if (this->square->piece != nullptr)
	{
		sf::Texture texture;
		texture.loadFromFile(this->square->getPieceName() + ".png", sf::IntRect(0, 0, 100, 100));
		texture.setSmooth(true);

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(this->coordinate);
		if (this->square->piece->color == true)
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

void RenderBoard::setSize(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
}

RenderBoard::RenderBoard()
{
	this->sqMat = new RenderSquare * [8];
	for (int i = 0; i < 8; ++i) {
		this->sqMat[i] = new RenderSquare[8];
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			this->sqMat[i][j].square = &(this->Board.board[i][j]);
		}
	}

	this->width = 800;
	this->height = 800;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0) {
				this->sqMat[i][j].color = true;
			}
			else {
				this->sqMat[i][j].color = false;
			}

			this->sqMat[i][j].coordinate = sf::Vector2f(j * 100, i * 100);
		}
	}

	// Black
	this->sqMat[0][0].square->piece = new Rook(false, Position(0, 0), 0);
	this->sqMat[0][1].square->piece = new Knight(false, Position(0, 1), 1);
	this->sqMat[0][2].square->piece = new Bishop(false, Position(0, 2), 2);
	this->sqMat[0][3].square->piece = new Queen(false, Position(0, 3), 3);
	this->sqMat[0][4].square->piece = new King(false, Position(0, 4), 4);
	this->sqMat[0][5].square->piece = new Bishop(false, Position(0, 5), 5);
	this->sqMat[0][6].square->piece = new Knight(false, Position(0, 6), 6);
	this->sqMat[0][7].square->piece = new Rook(false, Position(0, 7), 7);

	for (int j = 0; j < 8; j++)
	{
		this->sqMat[1][j].square->piece = new Pawn(false, Position(1, j), j + 8);
	}

	//white
	this->sqMat[7][0].square->piece = new Rook(true, Position(7, 0), 24);
	this->sqMat[7][1].square->piece = new Knight(true, Position(7, 1), 25);
	this->sqMat[7][2].square->piece = new Bishop(true, Position(7, 2), 26);
	this->sqMat[7][3].square->piece = new Queen(true, Position(7, 3), 27);
	this->sqMat[7][4].square->piece = new King(true, Position(7, 4), 28);
	this->sqMat[7][5].square->piece = new Bishop(true, Position(7, 5), 29);
	this->sqMat[7][6].square->piece = new Knight(true, Position(7, 6), 30);
	this->sqMat[7][7].square->piece = new Rook(true, Position(7, 7), 31);

	for (int j = 0; j < 8; j++)
	{
		this->sqMat[6][j].square->piece = new Pawn(true, Position(6, j), j + 16);
	}
}

void RenderBoard::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//	this->board[i][j].setSize(this->width / 8, this->height / 8);
			this->sqMat[i][j].draw(window);
		}
	}
}

RenderBoard::~RenderBoard()
{
	for (int i = 0; i < 8; ++i) {
		delete[] this->sqMat[i];
	}
	delete[] this->sqMat;
}


Manager::Manager()
{
	this->windowWidthScale = 1;
	this->windowHeightScale = 1;
	this->window.create(sf::VideoMode(950, 800), "Phú Xuân Chess!");
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
				sf::Vector2i mousePosition = sf::Vector2i(sf::Mouse::getPosition(this->window).x * 1.0f / this->windowWidthScale, sf::Mouse::getPosition(this->window).y * 1.0f / this->windowHeightScale);
				if (mousePosition.x <= 800)
				{
					Position vt = this->coordinateToPosition(mousePosition);
					//neu chua chon mot quan co truoc do thi hien len duong di cua quan co duoc chon  va phai den turn
					if (GameState::getInstance()->isPieceChoose == false &&
						this->b.sqMat[vt.i][vt.j].square->piece != nullptr &&
						GameState::getInstance()->turn == this->b.sqMat[vt.i][vt.j].square->piece->color)
					{
						if ((GameState::getInstance()->turn == true &&
							(((Mng::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == true &&
								dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
								Mng::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == false))) ||
							(GameState::getInstance()->turn == false &&
								(((Mng::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == true &&
									dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
									Mng::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == false)))
							)
						{
							GameState::getInstance()->isPieceChoose = true;
							this->window.clear();
							this->b.draw(this->window);

							pieceChoosen = this->b.Board.board[vt.i][vt.j].piece;
							canGo = this->b.Board.board[vt.i][vt.j].piece->canGo(this->b.Board);
							for (Position k : canGo)
							{
								this->b.sqMat[k.i][k.j].drawCanGo(this->window);
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