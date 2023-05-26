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

// Change state to NotSelected
void GUI::draw() {
	this->window.clear();
	this->render->draw(this->window);
	this->window.display();
}

// Change state to Selected
void GUI::drawCanGo(const Position& selectedSquare, vector<Position> cango) {

	this->window.clear();
	this->render->draw(this->window);
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
							this->drawCanGo(curPos, canGo);
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
						if (this->game->checkEndGame() != EndGameType::NoEndGame)
						{
							cout << "End Game";
						}
						this->draw();
					}

					// neu chon vao vi tri khong hop le, ta tro ve trang thai NotSelected
					else if (this->render->getState() == State::Selected)
					{
						this->render->setState(State::NotSelected);
						this->draw();
					}
				}
				//TESTTTTTTTTT
				else
				{
					this->game->undo();
					this->draw();
				}
			}
		}
	}
}