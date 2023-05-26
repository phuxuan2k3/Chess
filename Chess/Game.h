#pragma once
#include "Pieces.h"
#include "HistoryMove.h"

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

	King* whiteKing;
	King* blackKing;

	VectorMoves vecterMoves;

	Piece* initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j);
	Piece* initPieceOnBoard(PieceType pn, Troop pc, const Position& p);
public:
	GameState(Troop turn = Troop::White);
	// Will delete the pieces
	~GameState();
	bool promote = 0;
	PieceType PromoType;
	void switchTurn();
	// To connect the board in RenderGame
	const Board* getRefBoard() const;
	void PromotType(PieceType type, const Position& pos);
	// Determine if position chosen or move is valid
	Position getPiecePos();
	bool isValidChoice(const Position& pos) const;
	bool isValidMove(const Position& src, const Position& dest, vector<Position> canGo) const;
	// Return empty vector if pos is invalid, or that troop has no moves availible
	vector<Position> canGo(const Position& pos);
	// Return true on successful moves, false otherwise.
	void move(const Position& src, const Position& dest, vector<Position> canGo);
	void undo();
};
