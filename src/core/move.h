/**
 * @file move.h
 * @brief 移动信息结构体和相关类定义
 * @author yangyu
 * @date 2024
 * 
 * 本文件定义了与棋子移动相关的数据结构。
 */

#ifndef MOVE_H
#define MOVE_H

#include <cstdint>
#include <vector>

/**
 * @struct Move
 * @brief 移动信息结构体
 * 
 * 表示一个棋子的移动操作，包含源位置和目标位置。
 */
struct Move {
    int fromRow;  /**< 源行号 [0-7] */
    int fromCol;  /**< 源列号 [0-7] */
    int toRow;    /**< 目标行号 [0-7] */
    int toCol;    /**< 目标列号 [0-7] */

    /**
     * @brief 构造函数
     * @param fr 源行号
     * @param fc 源列号
     * @param tr 目标行号
     * @param tc 目标列号
     */
    Move(int fr = -1, int fc = -1, int tr = -1, int tc = -1)
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {}

    /**
     * @brief 检查移动是否有效
     * @return 移动是否有效
     */
    bool isValid() const {
        return fromRow >= 0 && fromRow < 8 &&
               fromCol >= 0 && fromCol < 8 &&
               toRow >= 0 && toRow < 8 &&
               toCol >= 0 && toCol < 8;
    }

    /**
     * @brief 检查两个移动是否相同
     * @param other 另一个移动
     * @return 是否相同
     */
    bool operator==(const Move& other) const {
        return fromRow == other.fromRow && fromCol == other.fromCol &&
               toRow == other.toRow && toCol == other.toCol;
    }
};

/**
 * @struct MoveRecord
 * @brief 移动历史记录
 * 
 * 记录一个完整的移动操作，包括移动信息、被吃掉的棋子和时间戳。
 */
struct MoveRecord {
    Move move;                  /**< 移动信息 */
    void* capturedPiece;        /**< 被吃掉的棋子指针（可能为 nullptr）*/
    int64_t timestamp;          /**< 时间戳（毫秒）*/
    bool isCastling;            /**< 是否为王车易位 */
    bool isEnPassant;           /**< 是否为 en passant 吃子 */
    bool isPawnPromotion;       /**< 是否为兵的升变 */

    /**
     * @brief 构造函数
     */
    MoveRecord(const Move& m = Move(), void* captured = nullptr,
               int64_t ts = 0, bool castle = false,
               bool enpass = false, bool promote = false)
        : move(m), capturedPiece(captured), timestamp(ts),
          isCastling(castle), isEnPassant(enpass),
          isPawnPromotion(promote) {}
};

#endif // MOVE_H
