#pragma once
#include "System.h"



class MoveEvent
{
private:
	Piece* moverPiece;		// Reference
	Piece* copySrcPiece;	// New memory
	Piece* copyDestPiece;	// New memory
	Position srcPos;
	Position destPos;

	Piece* eatenPiece;		// Reference
	Position eatPos;

	MoveEvent* castRookMove;	// A Rook move when king castled (Paired MoveEvent)

	Piece* promotePiece;	// Reference
	Position promPos;

	Piece* lastChoose;		// Reference to last chosen piece of that state (event)

public:
	// No promotion here
	MoveEvent(Piece* mover, const Position& srcPos, const Position& desPos, Piece* lastChoose);

	~MoveEvent();

	// Save - Load properties
	void saveSrcPieceInfo(Piece* const p);
	void saveDestPieceInfo(Piece* const p);
	void loadSrcPieceInfo(Piece* const p) const;
	void loadDestPieceInfo(Piece* const p) const;
	
	// Normal moves
	Piece* getMoverPiece() const;
	Position getSrcPos() const;
	Position getDestPos() const;

	// Eating moves
	bool isEatMove() const;
	Piece* getEatenPiece() const;
	Position getEatenPos() const;
	void setEatMove(Piece* eaten, const Position& pos);

	// Castling moves
	bool isCastlingMove() const;
	MoveEvent* getCastRookMove() const;
	void setCastRookMove(MoveEvent* castle);

	// Promote moves
	bool isPromoteMove() const;
	Piece* getPromotePiece() const;
	Position getPromotePos() const;
	// Trigger separately (not in move)
	void setPromote(Piece* promote, const Position& pos);

	Piece* getLastChoosePiece() const;
};


//=======================================================

// Stack style

class MoveHistory
{
private:
	MoveEvent* testMove;		// Moves for checking if king is in danger
	vector<MoveEvent*> moves;
	int state;

public:
	MoveHistory();
	~MoveHistory();

	void append(MoveEvent* me);

	void pushTestMove(MoveEvent* me);
	MoveEvent* getTestMove() const;

	MoveEvent* getCur() const;
	// These two should only be called when performed undo/redo
	void goBack();	// undo
	void goOn();	// redo

	// Clear all future events when triggered by moving
	// Pass in newly generated Piece for this function clean it
	void truncate(vector<Piece*> pieceNew);
};

