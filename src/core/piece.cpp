/**
 * @file piece.cpp
 * @brief 棋子类实现
 * @author yangyu
 * @date 2024
 */

#include "piece.h"

/**
 * @brief 构造函数实现
 */
Piece::Piece(PieceType type, PieceColor color, int row, int col)
    : m_type(type), m_color(color), m_row(row), m_col(col)
{
    // 构造函数体为空，所有初始化通过初始化列表完成
}

/**
 * @brief 设置棋子位置
 */
void Piece::setPosition(int row, int col)
{
    // 验证位置有效性（允许 -1 表示未放置）
    if ((row >= -1 && row < 8) && (col >= -1 && col < 8)) {
        m_row = row;
        m_col = col;
    }
}

/**
 * @brief 设置棋子贴图
 */
void Piece::setTexture(const QPixmap& pixmap)
{
    m_texture = pixmap;
}

/**
 * @brief 获取棋子类型的字符串表示
 */
QString Piece::getTypeName() const
{
    switch (m_type) {
        case PieceType::PAWN:   return "Pawn";
        case PieceType::KNIGHT: return "Knight";
        case PieceType::BISHOP: return "Bishop";
        case PieceType::ROOK:   return "Rook";
        case PieceType::QUEEN:  return "Queen";
        case PieceType::KING:   return "King";
        default:                return "Unknown";
    }
}

/**
 * @brief 获取棋子颜色的字符串表示
 */
QString Piece::getColorName() const
{
    return (m_color == PieceColor::WHITE) ? "White" : "Black";
}

/**
 * @brief 获取棋子的 FEN 符号
 * 
 * FEN 标准中的棋子符号：
 * - 白棋：P(兵), N(马), B(象), R(车), Q(后), K(王)
 * - 黑棋：p, n, b, r, q, k (小写)
 */
QString Piece::getFENSymbol() const
{
    QString symbol;
    
    switch (m_type) {
        case PieceType::PAWN:   symbol = "P"; break;
        case PieceType::KNIGHT: symbol = "N"; break;
        case PieceType::BISHOP: symbol = "B"; break;
        case PieceType::ROOK:   symbol = "R"; break;
        case PieceType::QUEEN:  symbol = "Q"; break;
        case PieceType::KING:   symbol = "K"; break;
    }
    
    // 黑棋符号转为小写
    if (m_color == PieceColor::BLACK) {
        symbol = symbol.toLower();
    }
    
    return symbol;
}
