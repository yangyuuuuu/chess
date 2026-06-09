/**
 * @file game.cpp
 * @brief 游戏管理器类实现
 * @author yangyu
 * @date 2024
 */

#include "game.h"
#include "../utils/logger.h"
#include <algorithm>
#include <ctime>

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::Game()
    : m_state(GameState::IDLE), m_currentPlayer(PieceColor::WHITE),
      m_winner(PieceColor::WHITE)
{
}

Game::~Game()
{
}

void Game::startNewGame()
{
    m_board.reset();
    m_moveHistory.clear();
    m_pieces.clear();
    initializeBoard();
    m_state = GameState::PLAYING;
    m_currentPlayer = PieceColor::WHITE;
    m_winner = PieceColor::WHITE;
}

bool Game::makeMove(int fromRow, int fromCol, int toRow, int toCol)
{
    if (m_state != GameState::PLAYING && m_state != GameState::CHECK) {
        return false;
    }

    if (!m_board.isValidPosition(fromRow, fromCol) || !m_board.isValidPosition(toRow, toCol)) {
        return false;
    }

    Piece* piece = m_board.getPiece(fromRow, fromCol);
    if (piece == nullptr) {
        return false;
    }

    if (piece->getColor() != m_currentPlayer) {
        return false;
    }

    Move move(fromRow, fromCol, toRow, toCol);
    if (!isMoveLegal(move)) {
        return false;
    }

    Piece* capturedPiece = m_board.getPiece(toRow, toCol);

    if (!m_board.movePiece(fromRow, fromCol, toRow, toCol)) {
        return false;
    }

    MoveRecord record(move, capturedPiece, static_cast<int64_t>(std::time(nullptr)));
    m_moveHistory.push_back(record);
    switchPlayer();
    updateGameState();

    return true;
}

bool Game::undoMove()
{
    if (m_moveHistory.empty()) {
        return false;
    }

    MoveRecord lastMove = m_moveHistory.back();
    Piece* piece = m_board.getPiece(lastMove.move.toRow, lastMove.move.toCol);
    if (piece == nullptr) {
        return false;
    }

    m_board.movePiece(lastMove.move.toRow, lastMove.move.toCol,
                      lastMove.move.fromRow, lastMove.move.fromCol);

    if (lastMove.capturedPiece != nullptr) {
        m_board.setPiece(lastMove.move.toRow, lastMove.move.toCol,
                        static_cast<Piece*>(lastMove.capturedPiece));
    }

    m_moveHistory.pop_back();
    switchPlayer();
    updateGameState();

    return true;
}

void Game::restartGame()
{
    startNewGame();
}

void Game::resign()
{
    m_state = GameState::GAME_OVER;
    m_winner = (m_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

bool Game::isGameOver() const
{
    return m_state == GameState::CHECKMATE || m_state == GameState::STALEMATE 
           || m_state == GameState::DRAW || m_state == GameState::GAME_OVER;
}

QString Game::getGameEndReason() const
{
    switch (m_state) {
        case GameState::CHECKMATE:
            return QString("%1 wins by checkmate").arg(
                m_winner == PieceColor::WHITE ? "White" : "Black");
        case GameState::STALEMATE:
            return "Draw by stalemate";
        case GameState::DRAW:
            return "Draw";
        case GameState::GAME_OVER:
            return "Game over";
        default:
            return "Game in progress";
    }
}

void Game::switchPlayer()
{
    m_currentPlayer = (m_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

void Game::initializeBoard()
{
    m_board.reset();
    m_pieces.clear();

    // 创建白棋
    for (int col = 0; col < 8; ++col) {
        auto pawn = std::make_unique<Piece>(PieceType::PAWN, PieceColor::WHITE, 6, col);
        m_board.setPiece(6, col, pawn.get());
        m_pieces.push_back(std::move(pawn));
    }

    // 白棋后排
    std::vector<PieceType> backRow = {
        PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN,
        PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK
    };

    for (int col = 0; col < 8; ++col) {
        auto piece = std::make_unique<Piece>(backRow[col], PieceColor::WHITE, 7, col);
        m_board.setPiece(7, col, piece.get());
        m_pieces.push_back(std::move(piece));
    }

    // 创建黑棋
    for (int col = 0; col < 8; ++col) {
        auto pawn = std::make_unique<Piece>(PieceType::PAWN, PieceColor::BLACK, 1, col);
        m_board.setPiece(1, col, pawn.get());
        m_pieces.push_back(std::move(pawn));
    }

    // 黑棋前排
    for (int col = 0; col < 8; ++col) {
        auto piece = std::make_unique<Piece>(backRow[col], PieceColor::BLACK, 0, col);
        m_board.setPiece(0, col, piece.get());
        m_pieces.push_back(std::move(piece));
    }
}

void Game::updateGameState()
{
    if (isCheckmate(m_currentPlayer)) {
        m_state = GameState::CHECKMATE;
        m_winner = (m_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
        return;
    }

    if (isStalemate(m_currentPlayer)) {
        m_state = GameState::STALEMATE;
        return;
    }

    if (isInCheck(m_currentPlayer)) {
        m_state = GameState::CHECK;
        return;
    }

    m_state = GameState::PLAYING;
}

const MoveRecord& Game::getLastMove() const
{
    static const MoveRecord invalidMove;
    return m_moveHistory.empty() ? invalidMove : m_moveHistory.back();
}

bool Game::isInCheck(PieceColor color) const
{
    Piece* king = m_board.getKing(color);
    if (king == nullptr) {
        return false;
    }
    return false; // 简化实现
}

bool Game::isCheckmate(PieceColor color) const
{
    return false; // 简化实现
}

bool Game::isStalemate(PieceColor color) const
{
    return false; // 简化实现
}

bool Game::wouldMoveExposeKing(Piece* piece, const Move& move) const
{
    return false; // 简化实现
}

std::vector<Move> Game::getLegalMoves(int row, int col) const
{
    return std::vector<Move>();
}

bool Game::isMoveLegal(const Move& move) const
{
    return true; // 简化实现
}
