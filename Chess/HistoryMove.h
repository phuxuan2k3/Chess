#pragma once
#include "System.h"



class MoveEvent
{
private:
	// New memory
	Piece* moverPiece;
	Piece* preInfoPiece;
	Position srcPos;
	Position destPos;
	
	// Only reference
	Piece* eatenPiece;
	Position eatPos;

public:
	MoveEvent(Piece* mover, const Position& srcPos, const Position& desPos, Piece* eaten, const Position& eatPos);
	~MoveEvent();

	// Load saved properties
	void loadMoverInfo(Piece* const p) const;
	Piece* getMover() const;
	Position getMoverSrc() const;
	Position getMoverDest() const;

	bool isEatMove() const;
	
	// Eating moves
	Piece* reviveEaten() const;
	Position getEatenPos() const;
};

//=======================================================

// Stack style

class MoveHistory
{
private:
	vector<MoveEvent*> moves;
	int state;

public:
	MoveHistory();
	~MoveHistory();

	void update(Piece* mover, const Position& srcPos, const Position& desPos, Piece* eaten, const Position& eatPos);

	MoveEvent* getCur() const;
	// These two should only be called when performed undo/redo
	void goBack();	// undo
	void goOn();	// redo

	// Clear all future events when triggered by moving
	void triggerChanged();
};

