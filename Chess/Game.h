#pragma once
#include "Pieces.h"

//=================================================================
// Handle the algorithm part

// Game will contain every things that needs for a chess game to be
// able to play. But not rendering, that will be left for RenderGame.
class GameState
{
private:
	PieceColor turn;
	Board board;

public:
	GameState(PieceColor turn = PieceColor::White);
	~GameState();

	PieceColor getTurn() const;
	const Board* getRefBoard() const;
	void switchTurn();
	void placePiece(PieceName pn, PieceColor pc, const int i, const int j);
	void placePiece(PieceName pn, PieceColor pc, const Position& p);
};
