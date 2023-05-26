#include "GameScreen.h"

GameScreen::GameScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game) : Screen(windowWidthScale, windowHeightScale, render, game) {}

void GameScreen::drawGameScreen(RenderWindow& window) {
	window.clear();
	this->render->draw(window);
	window.display();
}
void GameScreen::drawCanGo(RenderWindow& window, const Position& selectedSquare, vector<Position> cango) {
	window.clear();
	this->render->draw(window);
	this->render->drawCanGo(window, cango);
	window.display();
}
void GameScreen::run(RenderWindow& window, Screen*& screen, bool& end) {
	this->drawGameScreen(window);
	Position curPos;
	Position prePos;
	vector<Position> canGo;

	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				end = true;
			}

			else if (event.type == sf::Event::Resized)
			{
				this->windowWidthScale = window.getSize().x * 1.0f / 950;
				this->windowHeightScale = window.getSize().y * 1.0f / 800;
				this->drawGameScreen(window);
			}

			//xu ly su kien nhap chuot vao ban co
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				sf::Vector2i mousePosition =
					sf::Vector2i(
						sf::Mouse::getPosition(window).x * 1.0f / this->windowWidthScale,
						sf::Mouse::getPosition(window).y * 1.0f / this->windowHeightScale
					);

				// nhap chuot vao ban co
				if (mousePosition.x <= 800)
				{
					curPos = coordinateToPosition(mousePosition);

					//neu chua chon mot quan co truoc do thi hien len duong di cua quan co duoc chon  va phai den turn
					if (this->render->getState() == State::NotSelected &&
						this->game->isValidChoice(curPos) == true)
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
						canGo = this->game->canGo(curPos);
						// neu khong co nuoc di hop le, ta giu nguyen trang thai NotSelected
						// nguoc lai, ta chuyen ve tran thai Selected
						if (canGo.empty() == false) {
							this->render->setState(State::Selected);
							this->drawCanGo(window,curPos, canGo);
							prePos = curPos;
						}
					}

					// neu da chon mot quan co truoc do va chon vao 1 nuoc di hop le
					else if (this->render->getState() == State::Selected &&
						this->game->isValidMove(prePos, curPos, canGo) == true)
					{
						curPos = canGo[hasPosition(canGo, curPos)];		// Map curPos to canGo to get its type of move
						this->game->move(prePos, curPos, canGo);
						this->render->setState(State::NotSelected);
						this->game->switchTurn();
						this->drawGameScreen(window);
					}

					// neu chon vao vi tri khong hop le, ta tro ve trang thai NotSelected
					else if (this->render->getState() == State::Selected)
					{
						this->render->setState(State::NotSelected);
						this->drawGameScreen(window);
					}
				}
			}
		}
	}
}

