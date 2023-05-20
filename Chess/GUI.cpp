#include "GUI.h"

//===================================================
// GUI
//===================================================

GUI::GUI() {
	this->windowHeightScale = 1;
	this->windowWidthScale = 1;
	this->render = new RenderGame();
	this->game = new GameState();

	// Connect board
	this->render->setBoard(this->game->getRefBoard());
}

void GUI::draw() {
	this->window.clear();
	this->render->draw(this->window);
	this->window.display();
}

void GUI::drawCanGo(const Position& selectedSquare, vector<Position> cango) {

	this->window.clear();
	this->render->drawCanGo(this->window, cango);
	this->window.display();
}

void GUI::play()
{
	this->window.create(sf::VideoMode(950, 800), "");
	this->draw();

	Position curPos;
	Position prePos;
	vector<Position> canGo;

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
				this->draw();
			}

			//xu ly su kien nhap chuot vao ban co
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mousePosition =
					sf::Vector2i(
						sf::Mouse::getPosition(this->window).x * 1.0f / this->windowWidthScale,
						sf::Mouse::getPosition(this->window).y * 1.0f / this->windowHeightScale
					);

				if (mousePosition.x <= 800)
				{
					curPos = coordinateToPosition(mousePosition);

					//neu chua chon mot quan co truoc do thi hien len duong di cua quan co duoc chon  va phai den turn
					if (this->render->getState() == State::NotSelected &&
						this->game->getRefBoard()->getPiece(curPos) != nullptr &&
						this->game->getTurn() == this->game->getRefBoard()->getPiece(curPos)->getPieceColor())
					{
						// WTF ????
						//if ((GameState::getInstance()->turn == true &&
						//	(((GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == true &&
						//		dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
						//		GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[28]->pos.i, GameState::getInstance()->pieces[28]->pos.j), GameState::getInstance()->turn) == false))) ||
						//	(GameState::getInstance()->turn == false &&
						//		(((GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == true &&
						//			dynamic_cast<King*>(this->b.Board.board[vt.i][vt.j].piece)) ||
						//			GameHandle::isDangerousSquare(this->b.Board, Position(GameState::getInstance()->pieces[4]->pos.i, GameState::getInstance()->pieces[4]->pos.j), GameState::getInstance()->turn) == false)))
						//	)
						//{
						canGo = toPos(this->game->getRefBoard()->getPiece(curPos)->canGo());
						this->drawCanGo(curPos, canGo);
						prePos = curPos;
					}

					//neu da chon mot quan co truoc do thi thuc hien viec di chuyen
					else if (this->render->getState() == State::Selected &&
						curPos.find(canGo) == true
						)
					{
						this->game->getRefBoard()->getPiece(prePos)->move(curPos);
						this->game->switchTurn();
						this->draw();
					}
				}
			}
		}
	}
}