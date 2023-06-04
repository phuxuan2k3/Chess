#include "GameScreen.h"


GameScreen::GameScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game) : Screen(windowWidthScale, windowHeightScale, render, game) {
	this->gameb = GameBar::getInstance();
}

void GameScreen::drawGameScreen(RenderWindow& window) {
	window.clear();
	
	this->render->draw(window);
	this->gameb->showGameBar(window,game->isChecked());
	window.display();
}
void GameScreen::drawCanGo(RenderWindow& window, const Position& selectedSquare, vector<Position> cango) {
	window.clear();
	
	this->render->draw(window);
	this->render->drawCanGo(window, cango);
	this->render->drawSelected(window, selectedSquare);
	//this->gameb->showGameBar(window);
	this->gameb->showGameBar(window, game->isChecked());
	window.display();
}
void GameScreen::chessPos(RenderWindow& window)
{
	RenderPromote obj;
	obj.setRelaPos(window.getPosition());
}
void GameScreen::run(RenderWindow& window, Screen*& screen, bool& end) {
	bool notify = false;
	this->drawGameScreen(window);
	Position curPos;
	Position prePos;
	vector<Position> canGo;
	
	//Am thanh
	
	SoundBuffer soundB;
	soundB.loadFromFile("Audio/themSong.wav");
	Sound themSong;
	themSong.setBuffer(soundB);
	themSong.setLoop(true);
	themSong.setVolume(50);
	themSong.play();

	SoundBuffer checkB;
	checkB.loadFromFile("Audio/creepy-church-bell-33827.wav");
	Sound checked;
	checked.setLoop(true);
	checked.setBuffer(checkB);
	checked.setVolume(80);
	//checked.play();

	SoundBuffer pcB;
	pcB.loadFromFile("Audio/pc_3.wav");
	Sound pc;
	pc.setBuffer(pcB);
	pc.setVolume(50);

	SoundBuffer startGameB;
	startGameB.loadFromFile("Audio/dice_roll-96878.wav");
	Sound startGame;
	startGame.setBuffer(startGameB);
	startGame.setVolume(50);
	startGame.play();
	//pc.wav
	while (window.isOpen())
	{
		if (game->isChecked() && !notify) {
			checked.play();
			notify = true;
		}
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

				// Valid mouse click (in-board)
				if (mousePosition.x < 800 && mousePosition.x > 0 && mousePosition.y < 800)
				{
					// Map coordinate to Position on board
					curPos = coordinateToPosition(mousePosition);
					// Show AVAILIBLE MOVES
					if (this->render->getState() == State::NotSelected &&
						this->game->isValidChoice(curPos) == true)
					{
						sf::RectangleShape rec(sf::Vector2f(100, 100));
						rec.setPosition(curPos.get_i(), curPos.get_i());
						rec.setFillColor(sf::Color(245, 40, 145, 150));

						rec.setOutlineColor(sf::Color(255, 0, 0));
						rec.setOutlineThickness(50);
						window.draw(rec);
						this->game;
						canGo = this->game->canGo(curPos);

						// neu khong co nuoc di hop le, ta giu nguyen trang thai NotSelected
						// nguoc lai, ta chuyen ve tran thai Selected
						if (canGo.empty() == false) {
							this->render->setState(State::Selected);
							this->drawCanGo(window, curPos, canGo);
							prePos = curPos;
						}
					}
					// Perform MOVE
					else if (this->render->getState() == State::Selected && this->game->isValidMove(prePos, curPos, canGo) == true)
					{
						curPos = canGo[hasPosition(canGo, curPos)];		// Map curPos to canGo to get its type of move
						this->game->move(prePos, curPos, canGo);		// Turn changed here
						pc.play();
						this->game->checkEndGame();

						EndGameType tem = this->game->getIsEndGame();
						switch (tem)
						{
						case EndGameType::WhiteLose:
							cout << "WL" << endl;
							GameBar::updateEnded(1);
							this->drawGameScreen(window);
							break;
						case EndGameType::BlackLose:
							cout << "BL" << endl;
							GameBar::updateEnded(1);
							this->drawGameScreen(window);
							break;
						case EndGameType::Draw:
							cout << "D" << endl;
							GameBar::updateEnded(2);
							this->drawGameScreen(window);
							break;
						case EndGameType::NoEndGame:
							cout << "NEG" << endl;
							break;
						default:
							break;
						}

						this->render->setState(State::NotSelected);
						if (this->game->promote == true) {
							this->chessPos(window);
							this->game->PromotType(RenderPromote::drawPromotion(), curPos);
							this->game->promote = false;
							this->drawGameScreen(window);
						}

						GameBar::updateTurn();
						this->drawGameScreen(window);

						GameBar::timeline = GameBar::currentState + 1;
						GameBar::currentState = GameBar::timeline;
						checked.stop();
						notify = false;
					}

					// neu chon vao vi tri khong hop le, ta tro ve trang thai NotSelected
					else if (this->render->getState() == State::Selected)
					{
						this->render->setState(State::NotSelected);
						this->drawGameScreen(window);
					}
				}
				if (GameBar::undoBut.getGlobalBounds().contains(Vector2f(mousePosition)) && GameBar::ended == false && GameBar::isReplay == false) {
					if (GameBar::currentState > 0) {
						this->game->undo();
						GameBar::updateTurn();
						this->drawGameScreen(window);
						GameBar::currentState -= 1;
						checked.stop();
						notify = false;
					}
				}
				if (GameBar::redoBut.getGlobalBounds().contains(Vector2f(mousePosition)) && GameBar::ended == false && GameBar::isReplay == false) {
					if (GameBar::currentState < GameBar::timeline) {
						this->game->redo();
						GameBar::updateTurn();
						this->drawGameScreen(window);
						GameBar::currentState += 1;
					}
				}
				if (GameBar::saveBut.getGlobalBounds().contains(Vector2f(mousePosition)) && GameBar::ended == false && GameBar::isReplay == false) {
					cout << "save here";
					this->game->saveGame();
				}
				if (GameBar::homeBut.getGlobalBounds().contains(Vector2f(mousePosition))) {
					delete game;
					GameBar::currentState = 0;
					GameBar::timeline = 0;
					GameBar::ended = 0;
					GameBar::turn = Troop::White;
					game = new GameState();
					render->setBoard(game->getRefBoard());
					Screen* temp = screen;
					screen = new MenuScreen(this->windowWidthScale, this->windowHeightScale, render, game);
					delete temp;
					break;
				}
				if (GameBar::ended && GameBar::newGame.getGlobalBounds().contains(Vector2f(mousePosition))) {
					delete game;
					GameBar::currentState = 0;
					GameBar::timeline = 0;
					GameBar::ended = 0;
					GameBar::turn = Troop::White;
					game = new GameState();
					render->setBoard(game->getRefBoard());
					break;
				}
				if (GameBar::ended && GameBar::replay.getGlobalBounds().contains(Vector2f(mousePosition))) {
					while (GameBar::currentState != 0) {
						this->game->undo();
						GameBar::updateTurn();
						GameBar::currentState -= 1;
					}
					this->drawGameScreen(window);
					checked.stop();
					notify = false;
					GameBar::ended = false;
					GameBar::isReplay = true;
					Sleep(1500);
					while (GameBar::currentState < GameBar::timeline) {
						this->game->redo();
						GameBar::updateTurn();
						this->drawGameScreen(window);
						GameBar::currentState += 1;
						Sleep(1500);
					}
					GameBar::ended = true;
					GameBar::isReplay = false;
					break;
				}
			}
		}
	}
}

GameScreen::~GameScreen() {
	gameb->deleteInstance();
}
