#include "GameBar.h"
GameBar* GameBar::instance = NULL;
Troop GameBar::turn = Troop::White;
Text GameBar::turnText;
Sprite GameBar::undoBut;
Sprite GameBar::homeBut;
Text GameBar::selectedText;
PieceType GameBar::type;
Text GameBar::reset;
int GameBar::canUndo = 0;


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

void GameBar::updateSelected(PieceType t)
{
	type = t;
}

void GameBar::updateTurn() {
	if (turn == Troop::White) {
		turn = Troop::Black;
	}
	else {
		turn = Troop::White;
	}
}

void GameBar::showGameBar(RenderWindow& window) {
	//BackGroup  
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
	//Selected
	selectedText.setFont(turrnFont);

	selectedText.setPosition(bg.getPosition().x + 0.55 * textureBG.getSize().x * bg.getScale().x - 80, 0.5 * window.getSize().y);
	selectedText.setFillColor((Color::Black));
	selectedText.setCharacterSize(turnSize*0.5);
	selectedText.setOutlineThickness(2);

	selectedText.setOutlineColor(sf::Color(Color(90, 61, 43)));

	

	if (type == PieceType::Pawn) {
		selectedText.setString("PAWN");

	}
	if (type == PieceType::Bishop) {
		selectedText.setString("BISHOP");

	}
	if (type == PieceType::Knight) {
		selectedText.setString("KNIGHT");

	}
	if (type == PieceType::King) {
		selectedText.setString("KING");

	}
	if (type == PieceType::Queen) {
		selectedText.setString("QUEEN");

	}
	if (type == PieceType::Rook) {
		selectedText.setString("ROOK");

	}
	window.draw(selectedText);

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


}