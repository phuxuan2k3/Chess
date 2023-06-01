#pragma once
#include "Pieces.h"
#include "HistoryMove.h"
#include "EndGame.h"

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

	Position whiteKing;
	Position blackKing;

	MoveHistory vecterMoves;

	Piece* lastChoose;
	Piece* initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j);
	Piece* initPieceOnBoard(PieceType pn, Troop pc, const Position& p);

	EndGameType isEndGame;

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
	bool isValidChoice(const Position& pos) const;
	bool isValidMove(const Position& src, const Position& dest, vector<Position> canGo) const;
	// Return empty vector if pos is invalid, or that troop has no moves availible
	vector<Position> canGo(const Position& pos);
	// Return true on successful moves, false otherwise.
	bool isCanGo(Troop turn); // check can go or not ( can not move any where)
	void move(const Position& src, const Position& dest, vector<Position> canGo);
	void checkEndGame();
	EndGameType getIsEndGame() const;

	void undo();
};
