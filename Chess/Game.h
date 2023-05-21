#pragma once
#include "Pieces.h"

//=================================================================
// Handle the algorithm part

// Game will contain every things that needs for a chess game to be
// able to play. But not rendering, that will be left for RenderGame.
class GameState
{
private:
	Troop turn;
	Board board;
	vector<Piece*> pieces;
	void setConnection(King* king, Rook* lRook, Rook* rRook);

public:
	GameState(Troop turn = Troop::White);
	// Will delete the pieces
	~GameState();

	Troop getTurn() const;
	const Board* getRefBoard() const;
	void switchTurn();
	Piece* initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j);
	Piece* initPieceOnBoard(PieceType pn, Troop pc, const Position& p);
};
