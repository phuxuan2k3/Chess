#include "GameScreen.h"


GameScreen::GameScreen(float& windowWidthScale, float& windowHeightScale, RenderGame*& render, GameState*& game) : Screen(windowWidthScale, windowHeightScale, render, game) {
	this->gameb = GameBar::getInstance();
}

void GameScreen::drawGameScreen(RenderWindow& window) {
	window.clear();
	
	this->render->draw(window);
	this->gameb->showGameBar(window);
	window.display();
}
void GameScreen::drawCanGo(RenderWindow& window, const Position& selectedSquare, vector<Position> cango) {
	window.clear();
	
	this->render->draw(window);
	this->render->drawCanGo(window, cango);
	this->render->drawSelected(window, selectedSquare);
	//this->gameb->showGameBar(window);
	this->gameb->showGameBar(window);
	window.display();
}
void GameScreen::chessPos(RenderWindow& window)
{
	RenderPromote obj;
	obj.setRelaPos(window.getPosition());
}
void GameScreen::run(RenderWindow& window, Screen*& screen, bool& end) {

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
							GameBar::updateEnded();
							this->drawGameScreen(window);
							break;
						case EndGameType::BlackLose:
							cout << "BL" << endl;
							GameBar::updateEnded();
							this->drawGameScreen(window);
							break;
						case EndGameType::Draw:
							cout << "D" << endl;
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
						GameBar::timeline += 1;
						GameBar::currentState = GameBar::timeline;	// Once moved, it'll be set to current
					}

					// neu chon vao vi tri khong hop le, ta tro ve trang thai NotSelected
					else if (this->render->getState() == State::Selected)
					{
						this->render->setState(State::NotSelected);
						this->drawGameScreen(window);
					}
				}
				if (GameBar::undoBut.getGlobalBounds().contains(Vector2f(mousePosition)) && GameBar::ended == false) {
					if (GameBar::currentState > 0) {
						this->game->undo();
						GameBar::updateTurn();
						this->drawGameScreen(window);
						GameBar::currentState -= 1;
					}
				}
				if (GameBar::redoBut.getGlobalBounds().contains(Vector2f(mousePosition)) && GameBar::ended == false) {
					if (GameBar::currentState < GameBar::timeline) {
						this->game->redo();
						GameBar::updateTurn();
						this->drawGameScreen(window);
						GameBar::currentState += 1;
					}
				}
				if (GameBar::homeBut.getGlobalBounds().contains(Vector2f(mousePosition))) {
					Screen* temp = screen;
					screen = new MenuScreen(this->windowWidthScale, this->windowHeightScale, this->render, this->game);
					break;
				}
			}
		}
	}
}

GameScreen::~GameScreen() {
	gameb->deleteInstance();
}
