#include "GameBar.h"
GameBar* GameBar::instance = NULL;
Troop GameBar::turn = Troop::White;
Text GameBar::turnText;
Sprite GameBar::undoBut;
Sprite GameBar::homeBut;
Sprite GameBar::saveBut;
Sprite GameBar::replay;
Text GameBar::reset;
bool GameBar::isReplay = false;
Sprite GameBar::redoBut;
Sprite GameBar::newGame;
Sprite GameBar::checked;
int GameBar::ended = 0;

int GameBar::timeline = 0;
int GameBar::currentState = 0;


GameBar::GameBar() {
	
};

GameBar* GameBar::getInstance() {
	if (!instance) {
		return new GameBar();
	}
	return instance;
}
void GameBar::deleteInstance() {
	if (!instance) return;
	delete instance;
	instance = NULL;
}

void GameBar::updateTurn() {
	if (turn == Troop::White) {
		turn = Troop::Black;
	}
	else {
		turn = Troop::White;
	}
}

void GameBar::updateEnded(int i) {
	ended = i;
}

void GameBar::showGameBar(RenderWindow& window,bool isChecked) {
	
	//BackGround
	Texture textureBG;
	textureBG.loadFromFile("Image/gameBar.png");
	textureBG.setSmooth(true);
	Sprite bg;
	bg.setTexture(textureBG);
	bg.setPosition(float(0.67 * window.getSize().x), 0);
	bg.setScale(float(0.35 * window.getSize().x / textureBG.getSize().x), float(1.0 * window.getSize().y / textureBG.getSize().y));
	window.draw(bg);

	//TurnText
	Font turrnFont;
	double turnSize = 0.1 * window.getSize().y;
	turrnFont.loadFromFile("Font/gameFont_01.otf");
	turnText.setFont(turrnFont);
	turnText.setString((this->turn == Troop::White ? "White" : "Black"));
	turnText.setCharacterSize(turnSize);
	turnText.setFillColor((this->turn == Troop::White ? Color(255, 236, 180) : Color::Black));
	turnText.setOutlineColor(sf::Color(Color(90, 61, 43)));
	turnText.setOutlineThickness(2);
	turnText.setPosition(bg.getPosition().x + 0.5 * textureBG.getSize().x * bg.getScale().x - 80, 0.15 * window.getSize().y);
	window.draw(turnText);

	//checked
	Texture checkedTxt;
	checkedTxt.loadFromFile("Image/Warning-PNG-Free-Image.png");
	checkedTxt.setSmooth(true);
	Sprite checked;
	checked.setTexture(checkedTxt);
	checked.setPosition(bg.getPosition().x + 0.5 * textureBG.getSize().x * bg.getScale().x - 50, 0.3 * window.getSize().y);
	checked.setScale(0.2, 0.2);
	if (isChecked && !ended && !isReplay) window.draw(checked);


	float butScale = 0.3;
	//home button
	Texture homeTexture;
	homeTexture.loadFromFile("Image/homebut.png");
	homeTexture.setSmooth(true);
	homeBut.setTexture(homeTexture);
	homeBut.setPosition(bg.getPosition().x + 80 , turnText.getPosition().y + 300);
	homeBut.setScale(butScale, butScale);
	window.draw(homeBut);



	// Undo button
	Texture undoTexture;
	undoTexture.loadFromFile("Image/undoBut.png");
	undoTexture.setSmooth(true);
	undoBut.setTexture(undoTexture);
	undoBut.setPosition(bg.getPosition().x + 80 * 2, turnText.getPosition().y + 300);
	undoBut.setScale(butScale, butScale);
	window.draw(undoBut);



	// Redo button
	Texture redoTexture;
	redoTexture.loadFromFile("Image/redoBut.png");
	redoTexture.setSmooth(true);
	redoBut.setTexture(redoTexture);
	redoBut.setPosition(bg.getPosition().x + 80 * 3, turnText.getPosition().y + 300);
	redoBut.setScale(butScale, butScale);
	window.draw(redoBut);


	// Save button
	Texture saveTexture;
	saveTexture.loadFromFile("Image/save.png");
	saveTexture.setSmooth(true);
	saveBut.setTexture(saveTexture);
	saveBut.setPosition(bg.getPosition().x + 80, turnText.getPosition().y + 400);
	saveBut.setScale(butScale, butScale);
	window.draw(saveBut);



	
	//Ended
	if (ended !=0) {
		//newgame
		Texture ngTexture;
		ngTexture.loadFromFile("Image/newGame.png");
		ngTexture.setSmooth(true);
		newGame.setTexture(ngTexture);
		newGame.setScale(0.2, 0.2);
		newGame.setPosition(bg.getPosition().x + 0.5 * textureBG.getSize().x * bg.getScale().x - 80, 0.3 * window.getSize().y);
		window.draw(newGame);

		//replay
		Texture replayTet;
		replayTet.loadFromFile("Image/sup_replay.png");
		replayTet.setSmooth(true);
		replay.setTexture(replayTet);
		replay.setScale(0.3, 0.3);
		replay.setPosition(bg.getPosition().x + 0.5 * textureBG.getSize().x * bg.getScale().x - 70, 0.35 * window.getSize().y);
		window.draw(replay);

		cout << "in";
		Texture textureBG;
		textureBG.loadFromFile("Image/scroll.png");
		textureBG.setSmooth(true);
		bg.setTexture(textureBG);
		bg.scale(2.5, 2.5);
		bg.setPosition(0.5 * window.getSize().x - 450, 0.5 * window.getSize().y - 100);
		window.draw(bg);

		
		cout << "END";
		
		Font turrnFont;
		double turnSize = 0.08 * window.getSize().y;
		turrnFont.loadFromFile("Font/gameFont_01.otf");
		turnText.setFont(turrnFont);
		if(ended==1) turnText.setString((this->turn == Troop::White ? "Black Win" : "White Win"));
		if(ended==2) turnText.setString("Draw");
		turnText.setCharacterSize(turnSize);
		turnText.setFillColor(Color::Black);
		turnText.setOutlineColor(sf::Color(Color(90, 61, 43)));
		turnText.setOutlineThickness(2);
		turnText.setPosition(bg.getPosition().x + 100, bg.getPosition().y + 50);



		window.draw(turnText);

		
	}
}