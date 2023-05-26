#include "Game.h"
#include "StaticFunc.h"



//=======================================================
// // GameState
//=======================================================

GameState::GameState(Troop turn) {
	this->iEndGame = nullptr;
	this->turn = turn;

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
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::Black, 0, 4));
	((King*)(this->board.getPiece(0, 4)))->setPosition(Position(0, 4));
	this->blackKing = (King*)this->board.getPiece(0, 4);
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
	pieces.push_back(this->initPieceOnBoard(PieceType::King, Troop::White, 7, 4));
	((King*)(this->board.getPiece(7, 4)))->setPosition(Position(7, 4));
	this->whiteKing = (King*)this->board.getPiece(7, 4);
	pieces.push_back(this->initPieceOnBoard(PieceType::Bishop, Troop::White, 7, 5));
	pieces.push_back(this->initPieceOnBoard(PieceType::Knight, Troop::White, 7, 6));
	pieces.push_back(this->initPieceOnBoard(PieceType::Rook, Troop::White, 7, 7));

	// Setup connection
	// Black Side
	((King*)this->board.getPiece(0, 4))->setRooksPosition(
		Position(0, 0),
		Position(0, 7)
	);
	// White Side
	((King*)this->board.getPiece(7, 4))->setRooksPosition(
		Position(7, 0),
		Position(7, 7)
	);

}

GameState::~GameState()
{
	delete this->iEndGame;

	for (Piece* p : this->pieces) {
		delete p;
	}
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
		King* testwk = this->whiteKing;
		King* testbk = this->blackKing;
		if (isDangerousSquare((this->board.getPiece(res[i])->getTroop() == Troop::White ? this->whiteKing : this->blackKing)->getPosition(), this->board, this->board.getPiece(res[i])->getTroop()))
		{
			res.erase(res.begin() + i);
		}
		this->undo();
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
	//check move type
	if (dest.getInfo() == PosInfo::Promote) {
		this->promote = 1;

		
	}

	// Normal Move:	

	this->vecterMoves.deleteFrom(this->vecterMoves.getCurState() + 1);

	//if a king move, set its position
	if (King* king = dynamic_cast<King*>(this->board.getPiece(src)))
	{
		king->setPosition(dest);
	}

	Piece* copyPSrc = this->board.getPiece(src)->deepCopyPiece(this->board.getPiece(src));
	Piece* copyPDes = nullptr;

	Piece* pSrc = this->board.getPiece(src);
	pSrc->triggerOnFirstMove();

	// If dest Square is occupied by a Piece
	if (this->board.hasPiece(dest) == true) {
		copyPDes = this->board.getPiece(dest)->deepCopyPiece(this->board.getPiece(dest));

		//delete piece
		delete this->board.getPiece(dest);
		this->board.setPiece(dest, nullptr);

	}
	this->board.setPiece(dest, pSrc);
	this->board.setPiece(src, nullptr);
	this->board.lastChoose = pSrc;
	// Castling Move:

	if (pSrc->getTroop() == Troop::White) {
		this->board.EnPassantWhite = false;
	}
	else {
		this->board.EnPassantBlack = false;
	}


	if (dest.getInfo() == PosInfo::CastlingLeft) {
		Piece* leftRook = this->board.getPiece(((King*)pSrc)->getLeftRook());
		copyPDes = leftRook->deepCopyPiece(leftRook);
		this->move(((King*)pSrc)->getLeftRook(), src.getRelativePosition(0, -1), canGo);
	}
	else if (dest.getInfo() == PosInfo::CastlingRight) {
		Piece* rightRook = this->board.getPiece(((King*)pSrc)->getRightRook());
		copyPDes = rightRook->deepCopyPiece(rightRook);
		this->move(((King*)pSrc)->getRightRook(), src.getRelativePosition(0, 1), canGo);
	}
	else if (dest.getInfo() == PosInfo::PawnMovedTwoStep) {
		if (pSrc->getTroop() == Troop::White) {
			this->board.EnPassantBlack = true;
		}
		else {
			this->board.EnPassantWhite = true;
		}
	}
	else if (dest.getInfo() == PosInfo::EnPassant) {
		int dir = (pSrc->getTroop() == Troop::White ? 1 : -1);

		Piece* pawn = this->board.getPiece(dest.getRelativePosition(dir, 0));
		copyPDes = pawn->deepCopyPiece(pawn);

		//delete piece
		delete this->board.getPiece(dest.getRelativePosition(dir, 0));
		this->board.getPiece(dest.getRelativePosition(dir, 0))->setNull();
		this->board.setPiece(dest.getRelativePosition(dir, 0), nullptr);
	}

	this->board.getPiece(dest)->setNotNull();
	this->vecterMoves.pushBack(copyPSrc, copyPDes, src, dest);
}

void GameState::undo()
{
	if (this->vecterMoves.getCurState() >= 0)
	{
		Move lastMove = this->vecterMoves.getAt(this->vecterMoves.getCurState());

		this->vecterMoves.setCurState(this->vecterMoves.getCurState() - 1);

		if (King* king = dynamic_cast<King*>(lastMove.getMover()))
		{
			king->setPosition(lastMove.getSrcPos());
		}

		//delete
		if (this->board.getPiece(lastMove.getDesPos()))
		{
			this->board.getPiece(lastMove.getDesPos())->setNull();
			delete this->board.getPiece(lastMove.getDesPos());
			//this->board.getPiece(lastMove.getDesPos())->setNull();
			this->board.setPiece(lastMove.getDesPos(), nullptr);
		}

		Piece* newMover = lastMove.getCopyMover();
		this->board.setPiece(lastMove.getSrcPos(), newMover);
		this->board.getPiece(lastMove.getSrcPos())->setNotNull();
		//set king in gamestate a gain because new king is created
		if (King* king = dynamic_cast<King*>(newMover))
		{
			(newMover->getTroop() == Troop::White ? this->whiteKing : this->blackKing) = king;
		}

		int dir = 0;
		Position rookPos;
		switch (lastMove.getDesPos().getInfo())
		{
		case PosInfo::CastlingLeft:
			this->undo();
			//this->board.getPiece(lastMove.getDesPos())->setNull();
			//this->board.setPiece(((King*)lastMove.getMover())->getLeftRook(), lastMove.getCopyEaten());
			////delete rook
			//rookPos = lastMove.getDesPos().getRelativePosition(0, 1);
			//delete this->board.getPiece(rookPos);
			//this->board.getPiece(rookPos)->setNull();
			//this->board.setPiece(rookPos, nullptr);
			break;
		case PosInfo::CastlingRight:
			this->undo();
			//this->board.getPiece(lastMove.getDesPos())->setNull();
			 //this->board.setPiece(((King*)lastMove.getMover())->getRightRook(), lastMove.getCopyEaten());
			 ////delete rook
			 //rookPos = lastMove.getDesPos().getRelativePosition(0, -1);
			 //delete this->board.getPiece(rookPos);
			 //this->board.getPiece(rookPos)->setNull();
			 //this->board.setPiece(rookPos, nullptr);
			break;
		case PosInfo::EnPassant:
			dir = (lastMove.getCopyMover()->getTroop() == Troop::White ? 1 : -1);
			this->board.setPiece(lastMove.getDesPos().getRelativePosition(dir, 0), lastMove.getCopyEaten());
			break;
		default:
			if (lastMove.getEaten())
			{
				this->board.setPiece(lastMove.getDesPos(), lastMove.getCopyEaten());
				this->board.getPiece(lastMove.getDesPos())->setNotNull();
			}
			break;
		}
		this->turn = lastMove.getMover()->getTroop();

		if (this->vecterMoves.getCurState() >= 0)
		{
			this->board.lastChoose = this->vecterMoves.getAt(this->vecterMoves.getCurState()).getMover();
		}
		else
		{
			this->board.lastChoose = nullptr;
		}
	}
}

EndGameType GameState::checkEndGame()
{
	this->iEndGame = new LoseByCheckmate;
	EndGameType res = this->iEndGame->check(this->isCanGo(this->turn), this->turn == Troop::White ? this->whiteKing : this->blackKing, this->board);
	if (res != EndGameType::NoEndGame)
	{
		return res;
	}
	delete this->iEndGame;

	this->iEndGame = new DrawByStalemate;
	res = this->iEndGame->check(this->isCanGo(this->turn), this->turn == Troop::White ? this->whiteKing : this->blackKing, this->board);
	if (res != EndGameType::NoEndGame)
	{
		return res;
	}
	delete this->iEndGame;

	return EndGameType::NoEndGame;
}
