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

Troop GameState::getTurn() const {
	return this->turn;
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
	//Piece* rsses = this->board.getPiece(pos);		// asdfasdfm;admf;amf
	vector<Position> res = this->board.getPiece(pos)->canGo(pos, this->board);
	for (int i = res.size() - 1; i >= 0; i--)
	{
		// Call MOVE here
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
		//this->vecterMoves.truncate(this->promotePieces);
	}
	this->testState = false;
	return res;
}


bool GameState::isChecked() const {
	Position kingPos = this->turn == Troop::White ? this->whiteKing : this->blackKing;
	return isDangerousSquare(kingPos, this->board, this->turn);
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

	Piece* pSrc = this->board.getPiece(src);
	MoveEvent* me = new MoveEvent(pSrc, src, dest, this->lastChoose);

	// Update into history
	if (this->testState == false) {
		this->vecterMoves.truncate(this->promotePieces);
		this->vecterMoves.append(me);
	}
	else {
		this->vecterMoves.pushTestMove(me);
	}

	// If dest Square is occupied by a Piece => Just remove it from square, dont delete pls
	if (this->board.hasPiece(dest) == true) {
		// Update (before remove it from board)
		me->setEatMove(this->board.getPiece(dest), dest);
		this->board.setPiece(dest, nullptr);
	}
	// Castling Move: If it has passed all castling conditions, things will be fine
	else if (dest.getInfo() == PosInfo::CastlingLeft ||
		dest.getInfo() == PosInfo::CastlingRight) {
		bool left = dest.getInfo() == PosInfo::CastlingLeft;
		// Get rook and its position
		Position rookSrcPos = left ? ((King*)pSrc)->getLeftRook() : ((King*)pSrc)->getRightRook();
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
		me->setCastRookMove(castle);
	}
	// Enpassant
	else if (dest.getInfo() == PosInfo::EnPassant) {
		int dir = (pSrc->getTroop() == Troop::White ? 1 : -1);
		Position EnPassantPos = dest.getRelativePosition(dir, 0);
		// Update
		me->setEatMove(this->board.getPiece(EnPassantPos), EnPassantPos);
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
	me->saveSrcPieceInfo(pSrc);
	// Only update after moved
	pSrc->triggerOnMoved(dest);
	// Update post-state
	me->saveDestPieceInfo(pSrc);

	this->switchTurn();
}


void GameState::undo() {
	// Current state to undo, cause it save information of the piece before it get to this current postion
	// Set state to previous one (before castling to prevent loop)
	// If the state is 'empty' (starting or reached the current (for redo))
	MoveEvent* currentState = nullptr;
	if (this->testState == false) {
		currentState = this->vecterMoves.getCur();
		this->vecterMoves.goBack();
	}
	else {
		currentState = this->vecterMoves.getTestMove();
	}

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
	// Current state to undo, cause it save information of the piece before it get to this current postion
	// If the state is 'empty' (reached starting or current (for redo))
	// No testing with redo
	this->vecterMoves.goOn();
	MoveEvent* futureState = this->vecterMoves.getCur();
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

void GameState::saveGame()
{
	fstream file("chess.bin", ios::out | ios::binary);
	if (file.is_open())
	{
		file.write(reinterpret_cast<const char*>(&(this->turn)), sizeof(Troop));
		for (auto p : this->pieces)
		{
			p->savePiece(file);
			bool found = false;
			for (int i = 0; i < 8; i++)
			{
				if (found == true) break;
				for (int j = 0; j < 8; j++)
				{
					if (found == true) break;
					if (this->board.getPiece(Position(i, j)) == p)
					{
						Position pos(i, j);
						file.write(reinterpret_cast<const char*>(&pos), sizeof(Position));
						found = true;
					}
				}
			}
			if (found == false)
			{
				Position pos;
				file.write(reinterpret_cast<const char*>(&pos), sizeof(Position));
			}
		}
		//ghi them vi tri
		for (auto p : this->promotePieces)
		{
			PieceType pt = p->getPieceType();
			file.write(reinterpret_cast<const char*>(&pt), sizeof(PieceType));
			p->savePiece(file);
			bool found = false;
			for (int i = 0; i < 8; i++)
			{
				if (found == true) break;
				for (int j = 0; j < 8; j++)
				{
					if (found == true) break;
					if (this->board.getPiece(Position(i, j)) == p)
					{
						Position pos(i, j);
						file.write(reinterpret_cast<const char*>(&pos), sizeof(Position));
						found = true;
					}
				}
			}
			if (found == false)
			{
				Position pos;
				file.write(reinterpret_cast<const char*>(&pos), sizeof(Position));
			}
		}
	}
	else
	{
		cout << "Ghi ra file that bai!\n";
	}
	file.close();
}

void GameState::loadGame()
{
	for (Piece* p : this->pieces) {
		if (p) delete p;
	}
	for (Piece* p : this->promotePieces) {
		if (p) delete p;
	}
	this->pieces.clear();
	this->promotePieces.clear();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->board.setPiece(Position(i, j), nullptr);
		}
	}

	this->lastChoose = NullPiece::getInstance();

	fstream file("chess.bin", ios::in | ios::binary);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&(this->turn)), sizeof(Troop));
		for (int i = 0; i < 8; i++)
		{
			Piece* p = new Pawn(Troop::Black);
			file.read(reinterpret_cast<char*>(p), sizeof(Pawn));
			this->pieces.push_back(p);
			Position pos;
			file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
			if (pos.isNotNull())
			{
				this->board.setPiece(pos, p);
			}
		}

		Piece* r1 = new Rook(Troop::Black);
		file.read(reinterpret_cast<char*>(r1), sizeof(Rook));
		this->pieces.push_back(r1);
		Position pos;
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, r1);
		}
		Piece* k1 = new Knight(Troop::Black);
		file.read(reinterpret_cast<char*>(k1), sizeof(Knight));
		this->pieces.push_back(k1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, k1);
		}
		Piece* b1 = new Bishop(Troop::Black);
		file.read(reinterpret_cast<char*>(b1), sizeof(Bishop));
		this->pieces.push_back(b1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, b1);
		}
		Piece* q1 = new Queen(Troop::Black);
		file.read(reinterpret_cast<char*>(q1), sizeof(Queen));
		this->pieces.push_back(q1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, q1);
		}
		Piece* ki1 = new King(Troop::Black);
		file.read(reinterpret_cast<char*>(ki1), sizeof(King));
		this->pieces.push_back(ki1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, ki1);
			//vi tri con vua
			this->blackKing = pos;
		}
		Piece* b2 = new Bishop(Troop::Black);
		file.read(reinterpret_cast<char*>(b2), sizeof(Bishop));
		this->pieces.push_back(b2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, b2);
		}
		Piece* k2 = new Knight(Troop::Black);
		file.read(reinterpret_cast<char*>(k2), sizeof(Knight));
		this->pieces.push_back(k2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, k2);
		}
		Piece* r2 = new Rook(Troop::Black);
		file.read(reinterpret_cast<char*>(r2), sizeof(Rook));
		this->pieces.push_back(r2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, r2);
		}

		for (int i = 0; i < 8; i++)
		{
			Piece* p = new Pawn(Troop::White);
			file.read(reinterpret_cast<char*>(p), sizeof(Pawn));
			this->pieces.push_back(p);
			Position pos;
			file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
			if (pos.isNotNull())
			{
				this->board.setPiece(pos, p);
			}
		}

		r1 = new Rook(Troop::White);
		file.read(reinterpret_cast<char*>(r1), sizeof(Rook));
		this->pieces.push_back(r1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, r1);
		}
		k1 = new Knight(Troop::White);
		file.read(reinterpret_cast<char*>(k1), sizeof(Knight));
		this->pieces.push_back(k1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, k1);
		}
		b1 = new Bishop(Troop::White);
		file.read(reinterpret_cast<char*>(b1), sizeof(Bishop));
		this->pieces.push_back(b1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, b1);
		}
		q1 = new Queen(Troop::White);
		file.read(reinterpret_cast<char*>(q1), sizeof(Queen));
		this->pieces.push_back(q1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, q1);
		}
		ki1 = new King(Troop::White);
		file.read(reinterpret_cast<char*>(ki1), sizeof(King));
		this->pieces.push_back(ki1);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, ki1);
			//vi tri con vua
			this->whiteKing = pos;
		}
		b2 = new Bishop(Troop::White);
		file.read(reinterpret_cast<char*>(b2), sizeof(Bishop));
		this->pieces.push_back(b2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, b2);
		}
		k2 = new Knight(Troop::White);
		file.read(reinterpret_cast<char*>(k2), sizeof(Knight));
		this->pieces.push_back(k2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, k2);
		}
		r2 = new Rook(Troop::White);
		file.read(reinterpret_cast<char*>(r2), sizeof(Rook));
		this->pieces.push_back(r2);
		file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
		if (pos.isNotNull())
		{
			this->board.setPiece(pos, r2);
		}

		while (!file.eof())
		{
			Piece* p = nullptr;
			PieceType pt;
			file.read(reinterpret_cast<char*>(&pt), sizeof(PieceType));
			switch (pt)
			{
			case PieceType::Knight:
				p = new Knight(Troop::None);
				file.read(reinterpret_cast<char*>(p), sizeof(Knight));
				break;
			case PieceType::Bishop:
				p = new Bishop(Troop::None);
				file.read(reinterpret_cast<char*>(p), sizeof(Bishop));
				break;
			case PieceType::Rook:
				p = new Rook(Troop::None);
				file.read(reinterpret_cast<char*>(p), sizeof(Rook));
				break;
			case PieceType::Queen:
				p = new Queen(Troop::None);
				file.read(reinterpret_cast<char*>(p), sizeof(Queen));
				break;
			default:
				break;
			}
			if (p != nullptr) {
				this->promotePieces.push_back(p);
				Position pos;
				file.read(reinterpret_cast<char*>(&pos), sizeof(Position));
				if (pos.isNotNull())
				{
					this->board.setPiece(pos, p);
				}
			}
		}
	}
	else
	{
		cout << "Ghi ra file that bai!\n";
	}
	file.close();
}