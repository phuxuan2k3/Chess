#include "Game.h"
#include "StaticFunc.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(Troop turn) {
	this->turn = turn;
	this->lastChoose = NullPiece::getInstance();

	this->testState = false;

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
	for (Piece* p : this->pieces) {
		if (p) delete p;
	}
	for (Piece* p : this->promotePieces) {
		if (p) delete p;
	}
	this->pieces.clear();
	this->promotePieces.clear();
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


// Will generate new memory
void GameState::PromotType(PieceType type, const Position& pos)
{
	// Turn has changed previously, so we temperately change turn here
	this->switchTurn();
	Piece* promote = nullptr;
	if (type == PieceType::Bishop) {
		promote = new Bishop(this->turn);
		this->board.setPiece(pos, promote);
	}
	else if (type == PieceType::Knight) {
		promote = new Knight(this->turn);
		this->board.setPiece(pos, promote);
	}
	else if (type == PieceType::Rook) {
		promote = new Rook(this->turn);
		this->board.setPiece(pos, promote);
	}
	else if (type == PieceType::Queen) {
		promote = new Queen(this->turn);
		this->board.setPiece(pos, promote);
	}
	this->switchTurn();
	// Add to pieces to handle
	this->promotePieces.push_back(promote);
	// Update to the current timeline
	this->vecterMoves.getCur()->setPromote(promote, pos);
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
	// Test after move whether king is dangerous
	this->testState = true;
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
		this->vecterMoves.truncate(this->promotePieces);
	}
	this->testState = false;
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
	// For promotion: delete every newly promoted piece, by return the vector of pointer
	// of newly promoted piece
	this->vecterMoves.truncate(this->promotePieces);

	Piece* pSrc = this->board.getPiece(src);

	// Update into history
	this->vecterMoves.append(pSrc, src, dest, this->lastChoose);

	// If dest Square is occupied by a Piece => Just remove it from square, dont delete pls
	if (this->board.hasPiece(dest) == true) {
		// Update (before remove it from board)
		this->vecterMoves.getCur()->setEatMove(this->board.getPiece(dest), dest);
		this->board.setPiece(dest, nullptr);
	}
	// Castling Move: If it has passed all castling conditions, things will be fine
	else if (dest.getInfo() == PosInfo::CastlingLeft ||
		dest.getInfo() == PosInfo::CastlingRight) {
		bool left = dest.getInfo() == PosInfo::CastlingLeft;
		// Get rook and its position
		Position rookSrcPos =  left ? ((King*)pSrc)->getLeftRook() : ((King*)pSrc)->getRightRook();
		Position rookDestPos = left ? src.getRelativePosition(0, -1) : src.getRelativePosition(0, 1);
		Piece* rook = this->board.getPiece(rookSrcPos);
		this->board.setPiece(rookDestPos, rook);
		this->board.setPiece(rookSrcPos, nullptr);
		// Update
		MoveEvent* castle = new MoveEvent(rook, rookSrcPos, rookDestPos, nullptr);
		castle->saveSrcPieceInfo(rook);
		// Custom trigger
		rook->triggerOnMoved(dest);
		castle->saveDestPieceInfo(rook);
		this->vecterMoves.getCur()->setCastRookMove(castle);
	}
	// Enpassant
	else if (dest.getInfo() == PosInfo::EnPassant) {
		int dir = (pSrc->getTroop() == Troop::White ? 1 : -1);
		Position EnPassantPos = dest.getRelativePosition(dir, 0);
		// Update
		this->vecterMoves.getCur()->setEatMove(this->board.getPiece(EnPassantPos), EnPassantPos);
		this->board.setPiece(EnPassantPos, nullptr);
	}

	// Main MOVE action:
	// Set piece to its destinaiton
	this->board.setPiece(dest, pSrc);
	this->board.setPiece(src, nullptr);

	// Update king's position: If the piece moved is the king
	if (pSrc->isKing() == true)
	{
		(this->turn == Troop::White ? this->whiteKing : this->blackKing) = dest;
	}
	// Check promote (for Pawns only), update into history with a PromoteEvent -> MoveEvent
	if (dest.getInfo() == PosInfo::Promote) {
		// If it's test state we dont trigger promote
		if (this->testState != true) {
			this->promote = true;
		}
	}

	// Update last chosen piece
	this->lastChoose->setNotLastChosen();
	this->lastChoose = pSrc;
	this->lastChoose->setLastChosen();

	// Update pre-state
	this->vecterMoves.getCur()->saveSrcPieceInfo(pSrc);
	// Only update after moved
	pSrc->triggerOnMoved(dest);
	// Update post-state
	this->vecterMoves.getCur()->saveDestPieceInfo(pSrc);

	this->switchTurn();
}


void GameState::undo() {
	// Current state to undo, cause it save information of the piece before it get to this current postion
	MoveEvent* currentState = this->vecterMoves.getCur();
	// Set state to previous one (before castling to prevent loop)
	this->vecterMoves.goBack();
	// If the state is 'empty' (starting or reached the current (for redo))
	if (currentState == nullptr) {
		// Set last choose back to null
		this->lastChoose = NullPiece::getInstance();
		return;
	}

	Piece* pieceToUndo = currentState->getMoverPiece();

	// Main UNDO
	// Place piece back to its preious position, and load its info
	this->board.setPiece(currentState->getDestPos(), nullptr);
	this->board.setPiece(currentState->getSrcPos(), pieceToUndo);
	currentState->loadSrcPieceInfo(pieceToUndo);

	// Revive eaten piece: place back the pointer
	if (currentState->isEatMove() == true) {
		this->board.setPiece(currentState->getEatenPos(), currentState->getEatenPiece());
	}

	// No need to check Promote move in undo

	// Castling
	if (currentState->isCastlingMove() == true)
	{
		MoveEvent* rookCastleEvent = currentState->getCastRookMove();
		Piece* rookToUndo = rookCastleEvent->getMoverPiece();
		this->board.setPiece(rookCastleEvent->getDestPos(), nullptr);
		this->board.setPiece(rookCastleEvent->getSrcPos(), rookToUndo);
		rookCastleEvent->loadSrcPieceInfo(rookToUndo);
	}

	// Update King's Position (reversed because not switched turn, current turn is opponent's)
	if (pieceToUndo->isKing() == true)
	{
		(this->turn != Troop::White ? this->whiteKing : this->blackKing) = currentState->getSrcPos();
	}
	
	this->switchTurn();

	// Set last chosen piece of that state
	this->lastChoose->setNotLastChosen();
	this->lastChoose = currentState->getLastChoosePiece();
	this->lastChoose->setLastChosen();
}


void GameState::redo() {
	// Set state to later one (its future state), then we consider it as current state
	// and reverse all undo operations
	this->vecterMoves.goOn();
	// Current state to undo, cause it save information of the piece before it get to this current postion
	MoveEvent* futureState = this->vecterMoves.getCur();
	// If the state is 'empty' (reached starting or current (for redo))
	if (futureState == nullptr) {
		return;
	}

	Piece* pieceToRedo = futureState->getMoverPiece();

	// Main REDO
	// Move piece to its future position
	this->board.setPiece(futureState->getSrcPos(), nullptr);
	this->board.setPiece(futureState->getDestPos(), pieceToRedo);
	futureState->loadDestPieceInfo(pieceToRedo);

	// Kill the eaten piece (if its hasn't been replaced)
	if (futureState->isEatMove() == true &&
		!(futureState->getDestPos() == futureState->getEatenPos())) 
	{
		this->board.setPiece(futureState->getEatenPos(), nullptr);
	}

	// If Promote, replace it with the Promote piece
	if (futureState->isPromoteMove()) {
		this->board.setPiece(futureState->getDestPos(), futureState->getPromotePiece());
	}

	// Castling
	if (futureState->isCastlingMove() == true)
	{
		MoveEvent* rookCastleEvent = futureState->getCastRookMove();
		Piece* rookToRedo = rookCastleEvent->getMoverPiece();
		this->board.setPiece(rookCastleEvent->getSrcPos(), nullptr);
		this->board.setPiece(rookCastleEvent->getDestPos(), rookToRedo);
		rookCastleEvent->loadDestPieceInfo(rookToRedo);
	}
	
	// Update King's Position (reversed because not switched turn, current turn is opponent's)
	if (pieceToRedo->isKing() == true)
	{
		(this->turn != Troop::White ? this->whiteKing : this->blackKing) = futureState->getSrcPos();
	}

	this->switchTurn();

	// Set last chosen piece of that state
	this->lastChoose->setNotLastChosen();
	this->lastChoose = futureState->getLastChoosePiece();
	this->lastChoose->setLastChosen();
}


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
