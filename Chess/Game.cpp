#include "Game.h"
#include "StaticFunc.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(Troop turn) {
	this->turn = turn;
	this->lastChoose = NullPiece::getInstance();

	// Default Placing 

	// Black

	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::Black, 1, 7));

	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::Black, 0, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::Black, 0, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::Black, 0, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Queen, Troop::Black, 0, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::Black, 0, 4));	// King
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::Black, 0, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::Black, 0, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::Black, 0, 7));
	

	// White

	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 4));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Pawn, Troop::White, 6, 7));

	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::White, 7, 0));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::White, 7, 1));
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::White, 7, 2));
	pieces.push_back(this->initPieceOnBoard(PieceType::Queen, Troop::White, 7, 3));
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::White, 7, 4));	// King
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::White, 7, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::White, 7, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::White, 7, 7));


	// Setup connection
	// Black Side
	this->blackKing = Position(0, 4);
	((King*)this->board.getPiece(0, 4))->setRooksPosition(
		Position(0, 0),
		Position(0, 7)
	);
	// White Side
	this->whiteKing = Position(7, 4);
	((King*)this->board.getPiece(7, 4))->setRooksPosition(
		Position(7, 0),
		Position(7, 7)
	);

}

GameState::~GameState()
{
}

void GameState::switchTurn() {
	if (this->turn == Troop::Black) {
		this->turn = Troop::White;
	}
	else {
		this->turn = Troop::Black;
	}
}

const Board* GameState::getRefBoard() const {
	return &this->board;
}

void GameState::PromotType(PieceType type, const Position& pos)
{
	if (type == PieceType::Bishop) {
		Piece* promote = new Bishop(this->turn);
		this->board.setPiece(pos, promote);
	}
	if (type == PieceType::Knight) {
		Piece* promote = new Knight(this->turn);
		this->board.setPiece(pos, promote);

	}
	if (type == PieceType::Rook) {
		Piece* promote = new Rook(this->turn);
		this->board.setPiece(pos, promote);

	}
	if (type == PieceType::Queen) {
		Piece* promote = new Queen(this->turn);
		this->board.setPiece(pos, promote);

	}
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const int i, const int j) {
	Piece* piece = nullptr;
	switch (pn)
	{
	case PieceType::Pawn:
		piece = new Pawn(pc);
		break;
	case PieceType::Knight:
		piece = new Knight(pc);
		break;
	case PieceType::Bishop:
		piece = new Bishop(pc);
		break;
	case PieceType::Rook:
		piece = new Rook(pc);
		break;
	case PieceType::Queen:
		piece = new Queen(pc);
		break;
	case PieceType::King:
		piece = new King(pc);
		break;
	default:
		break;
	}

	this->board.setPiece(i, j, piece);
	return piece;
}

Piece* GameState::initPieceOnBoard(PieceType pn, Troop pc, const Position& p) {
	return this->initPieceOnBoard(pn, pc, p.get_i(), p.get_j());
}

bool GameState::isValidChoice(const Position& pos) const {
	Piece* piece = this->board.getPiece(pos);
	// If there isn't any piece
	if (piece == nullptr) {
		return false;
	}
	// Not valid turn
	if (piece->getTroop() != this->turn) {
		return false;
	}
	return true;
}

vector<Position> GameState::canGo(const Position& pos) {
	if (this->board.hasPiece(pos) == false) {
		return vector<Position>();
	}
	//Test after move whether king is dangerous
	vector<Position> res = this->board.getPiece(pos)->canGo(pos, this->board);
	for (int i = res.size() - 1; i >= 0; i--)
	{
		this->move(pos, res[i], res);
		Position testwk = this->whiteKing;
		Position testbk = this->blackKing;
		if (isDangerousSquare(
			(this->board.getPiece(res[i])->getTroop() == Troop::White ? this->whiteKing : this->blackKing),
			this->board,
			this->board.getPiece(res[i])->getTroop()))
		{
			res.erase(res.begin() + i);
		}
		this->undo();
		// These are fake moves so don't add into history
		this->vecterMoves.truncate();
	}

	return res;
}

bool GameState::isValidMove(const Position& src, const Position& dest, vector<Position> canGo) const {
	// If the src Square chosen is empty, we do nothing
	if (this->board.hasPiece(src) == false) {
		return false;
	}
	// If dest Square is not in canGo
	if (hasPosition(canGo, dest) == -1) {
		return false;
	}
	return true;
}

bool GameState::isCanGo(Troop turn)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (this->board.board[i][j].getPiece() != nullptr and this->board.board[i][j].getPiece()->getTroop() == turn)
			{
				if (this->canGo(Position(i, j)).empty() == false)
				{
					return true;
				}
			}
		}
	}
	return false;
}


void GameState::move(const Position& src, const Position& dest, vector<Position> canGo) {
	// Change move history => No redo once moved
	this->vecterMoves.truncate();

	Piece* pSrc = this->board.getPiece(src);
	Piece* pEaten = nullptr;
	Position eatPos;

	// Check promote
	if (dest.getInfo() == PosInfo::Promote) {
		this->promote = 1;
	}

	// If dest Square is occupied by a Piece => Just remove it from square, dont delete pls
	if (this->board.hasPiece(dest) == true) {
		pEaten = this->board.getPiece(dest);
		eatPos = dest;
		this->board.setPiece(dest, nullptr);
	}
	// Castling Move:
	else if (dest.getInfo() == PosInfo::CastlingLeft) {
		Piece* leftRook = this->board.getPiece(((King*)pSrc)->getLeftRook());
		this->move(((King*)pSrc)->getLeftRook(), src.getRelativePosition(0, -1), canGo);
	}
	else if (dest.getInfo() == PosInfo::CastlingRight) {
		Piece* rightRook = this->board.getPiece(((King*)pSrc)->getRightRook());
		this->move(((King*)pSrc)->getRightRook(), src.getRelativePosition(0, 1), canGo);
	}
	// Enpassant
	else if (dest.getInfo() == PosInfo::EnPassant) {
		int dir = (pSrc->getTroop() == Troop::White ? 1 : -1);
		Position EnPassantPos = dest.getRelativePosition(dir, 0);
		pEaten = this->board.getPiece(EnPassantPos);
		eatPos = EnPassantPos;
		this->board.setPiece(EnPassantPos, nullptr);
	}

	// Set piece to its destinaiton
	this->board.setPiece(dest, pSrc);
	this->board.setPiece(src, nullptr);

	// Update king's position: If the piece moved is the king
	if (pSrc->isKing() == true)
	{
		(this->turn == Troop::White ? this->whiteKing : this->blackKing) = dest;
	}

	// Update into history
	this->vecterMoves.append(pSrc, src, dest, pEaten, eatPos);

	// Update last chosen piece
	this->lastChoose->setNotLastChosen();
	this->lastChoose = pSrc;
	this->lastChoose->setLastChosen();

	// Only update after moved
	pSrc->triggerOnMoved(dest);

	this->switchTurn();
	
}


void GameState::undo() {
	// Current state to undo, cause it save information of the piece before it get to this current postion
	MoveEvent* currentState = this->vecterMoves.getCur();
	// If the state is 'empty' (starting or reached the current (for redo))
	if (currentState == nullptr) {
		// Do nothing
		return;
	}

	if (this->board.hasPiece(currentState->getMoverDest()) == false) {
		throw exception();
	}

	Piece* pieceThatReturn = this->board.getPiece(currentState->getMoverDest());

	// Return undo piece to its previous position and copy its previous properties into it.
	this->board.setPiece(currentState->getMoverDest(), nullptr);
	this->board.setPiece(currentState->getMoverSrc(), pieceThatReturn);
	currentState->loadMoverInfo(pieceThatReturn);

	// Update King's Position (reversed because not switched turn)
	if (pieceThatReturn->isKing() == true)
	{
		(this->turn != Troop::White ? this->whiteKing : this->blackKing) = currentState->getMoverSrc();
	}

	// Revive eaten piece: place back the pointer
	if (currentState->isEatMove() == true) {
		this->board.setPiece(currentState->getEatenPos(), currentState->reviveEaten());
	}

	// Set state to previous one
	this->vecterMoves.goBack();

	// Special: Castling - moved twice, so we undo twice, (must go back first)
	if (currentState->getMoverDest().getInfo() == PosInfo::CastlingRight ||
		currentState->getMoverDest().getInfo() == PosInfo::CastlingLeft)
	{
		this->undo();
	}

	this->switchTurn();

	// Last piece chosen. Note: since it has gone back, the piece used here is the previous state's piece
	// also the last chosen piece
	// Reached its start
	if (this->vecterMoves.getCur() == nullptr) {
		this->lastChoose = NullPiece::getInstance();
	}
	else {
		// Get its reference
		// Note: it has already set to be chosen because of the copy into memory (?)
		this->lastChoose->setNotLastChosen();
		this->lastChoose = this->vecterMoves.getCur()->getMover();
		this->lastChoose->setLastChosen();
	}
}

//
//void GameState::undo()
//{
//	if (this->vecterMoves.getCurState() >= 0)
//	{
//		MoveEvent lastMove = this->vecterMoves.getAt(this->vecterMoves.getCurState());
//
//		this->vecterMoves.setCurState(this->vecterMoves.getCurState() - 1);
//
//		if (King* king = dynamic_cast<King*>(lastMove.getMover()))
//		{
//			king->setPosition(lastMove.getMoverSrc());
//		}
//
//		//delete piece at its current position
//		if (this->board.getPiece(lastMove.getMoverDest()))
//		{
//			delete this->board.getPiece(lastMove.getMoverDest());
//			this->board.setPiece(lastMove.getMoverDest(), nullptr);
//		}
//
		//Piece* newMover = lastMove.getCopyMover();
		//this->board.setPiece(lastMove.getMoverSrc(), newMover);
		////set king in gamestate a gain because new king is created
		//if (King* king = dynamic_cast<King*>(newMover))
		//{
		//	(newMover->getTroop() == Troop::White ? this->whiteKing : this->blackKing) = king;
		//}
//
//		int dir = 0;
//		Position rookPos;
//		switch (lastMove.getMoverDest().getInfo())
//		{
//		case PosInfo::CastlingLeft:
//			this->undo();
//			break;
//		case PosInfo::CastlingRight:
//			this->undo();
//			break;
//		case PosInfo::EnPassant:
//			dir = (lastMove.getCopyMover()->getTroop() == Troop::White ? 1 : -1);
//			this->board.setPiece(lastMove.getMoverDest().getRelativePosition(dir, 0), lastMove.getCopyEaten());
//			break;
//		default:
//			if (lastMove.getEaten())
//			{
//				this->board.setPiece(lastMove.getMoverDest(), lastMove.getCopyEaten());
//			}
//			break;
//		}
//		this->turn = lastMove.getMover()->getTroop();
//
//		if (this->vecterMoves.getCurState() >= 0)
//		{
//			this->lastChoose = this->vecterMoves.getAt(this->vecterMoves.getCurState()).getMover();
//		}
//		else
//		{
//			this->lastChoose = NullPiece::getInstance();
//		}
//	}
//}

EndGameType GameState::getIsEndGame() const {
	return this->isEndGame;
}

void GameState::checkEndGame()
{
	IEndGame* iEndGame = nullptr;

	iEndGame = new LoseByCheckmate;
	EndGameType res = iEndGame->check(
		this->isCanGo(this->turn),
		this->turn == Troop::White ? this->whiteKing : this->blackKing,
		this->board,
		this->turn);
	if (res != EndGameType::NoEndGame)
	{
		this->isEndGame = res;
		delete iEndGame;
		return;
	}

	iEndGame = new DrawByStalemate;
	res = iEndGame->check(
		this->isCanGo(this->turn),
		this->turn == Troop::White ? this->whiteKing : this->blackKing,
		this->board,
		this->turn);
	if (res != EndGameType::NoEndGame)
	{
		this->isEndGame = res;
		delete iEndGame;
		return;
	}

	delete iEndGame;
	this->isEndGame = EndGameType::NoEndGame;
}
