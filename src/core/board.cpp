/**
 * @file board.cpp
 * @brief 棋盘类实现
 * @author yangyu
 * @date 2024
 */

#include "board.h"

/**
 * @brief 棋盘构造函数
 * 初始化所有位置为空（nullptr）
 */
Board::Board()
{
    // 初始化棋盘为空
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            m_board[i][j] = nullptr;
        }
    }
}

/**
 * @brief 棋盘析构函数
 */
Board::~Board()
{
    // 棋子由 Game 类拥有和管理，这里不需要删除
}

/**
 * @brief 获取指定位置的棋子
 */
Piece* Board::getPiece(int row, int col) const
{
    // 检查位置有效性
    if (!isValidPosition(row, col)) {
        return nullptr;
    }
    return m_board[row][col];
}

/**
 * @brief 设置指定位置的棋子
 */
void Board::setPiece(int row, int col, Piece* piece)
{
    // 检查位置有效性
    if (!isValidPosition(row, col)) {
        return;
    }
    m_board[row][col] = piece;
}

/**
 * @brief 检查位置是否有效
 */
bool Board::isValidPosition(int row, int col) const
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

/**
 * @brief 检查位置是否被占据
 */
bool Board::isOccupied(int row, int col) const
{
    if (!isValidPosition(row, col)) {
        return false;
    }
    return m_board[row][col] != nullptr;
}

/**
 * @brief 检查是否有指定颜色的棋子
 */
bool Board::hasColoredPiece(int row, int col, PieceColor color) const
{
    Piece* piece = getPiece(row, col);
    return (piece != nullptr && piece->getColor() == color);
}

/**
 * @brief 移动棋子
 */
bool Board::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
    // 验证源位置有效性
    if (!isValidPosition(fromRow, fromCol)) {
        return false;
    }

    // 验证目标位置有效性
    if (!isValidPosition(toRow, toCol)) {
        return false;
    }

    // 获取源位置的棋子
    Piece* piece = m_board[fromRow][fromCol];
    if (piece == nullptr) {
        return false;  // 源位置没有棋子
    }

    // 移动棋子
    m_board[toRow][toCol] = piece;      // 在目标位置放置棋子
    m_board[fromRow][fromCol] = nullptr; // 清除源位置

    // 更新棋子的位置信息
    piece->setPosition(toRow, toCol);

    return true;
}

/**
 * @brief 移除棋子（吃子操作）
 */
Piece* Board::removePiece(int row, int col)
{
    if (!isValidPosition(row, col)) {
        return nullptr;
    }

    Piece* piece = m_board[row][col];
    m_board[row][col] = nullptr;
    return piece;
}

/**
 * @brief 重置棋盘
 */
void Board::reset()
{
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            m_board[i][j] = nullptr;
        }
    }
}

/**
 * @brief 获取所有棋子
 */
std::vector<Piece*> Board::getAllPieces() const
{
    std::vector<Piece*> pieces;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (m_board[i][j] != nullptr) {
                pieces.push_back(m_board[i][j]);
            }
        }
    }
    return pieces;
}

/**
 * @brief 获取指定颜色的所有棋子
 */
std::vector<Piece*> Board::getPiecesByColor(PieceColor color) const
{
    std::vector<Piece*> pieces;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Piece* piece = m_board[i][j];
            if (piece != nullptr && piece->getColor() == color) {
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

/**
 * @brief 获取指定颜色和类型的棋子
 */
std::vector<Piece*> Board::getPiecesByColorAndType(
    PieceColor color, PieceType type) const
{
    std::vector<Piece*> pieces;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Piece* piece = m_board[i][j];
            if (piece != nullptr && piece->getColor() == color 
                && piece->getType() == type) {
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

/**
 * @brief 获取指定颜色的王
 */
Piece* Board::getKing(PieceColor color) const
{
    auto kings = getPiecesByColorAndType(color, PieceType::KING);
    return kings.empty() ? nullptr : kings[0];
}

/**
 * @brief 获取原始棋盘数组
 */
Piece* const (*Board::getRawBoard())[BOARD_SIZE]
{
    return &m_board;
}
