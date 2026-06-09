/**
 * @file board.h
 * @brief 棋盘类定义
 * @author yangyu
 * @date 2024
 * 
 * 本文件定义了棋盘类，管理 8x8 国际象棋棋盘。
 * 棋盘类负责：
 * - 棋盘的初始化
 * - 棋子位置的管理
 * - 棋子的放置和移除
 * - 棋子查询接口
 */

#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <vector>
#include <memory>

/**
 * @class Board
 * @brief 棋盘类
 * 
 * 管理国际象棋的 8x8 棋盘。采用二维数组存储棋子，
 * 每个位置可以为空（nullptr）或包含一个棋子指针。
 * 
 * 坐标系统：
 * - 行号：0 为黑棋起始行，7 为白棋起始行
 * - 列号：0 为 a 文件，7 为 h 文件
 * 
 * @note 棋盘不拥有棋子的所有权，棋子由 Game 类管理
 */
class Board {
public:
    /**
     * @brief 棋盘大小常数
     * 国际象棋标准棋盘为 8x8
     */
    static const int BOARD_SIZE = 8;

    /**
     * @brief 构造函数
     * 初始化一个空棋盘（所有位置都为 nullptr）
     */
    Board();

    /**
     * @brief 析构函数
     * 清理棋盘资源（棋子由 Game 类拥有和清理）
     */
    ~Board();

    /**
     * @brief 复制构造函数删除
     * 棋盘不支持复制操作，避免棋子指针混乱
     */
    Board(const Board&) = delete;

    /**
     * @brief 赋值操作符删除
     */
    Board& operator=(const Board&) = delete;

    // ===================== 棋子查询接口 =====================

    /**
     * @brief 获取指定位置的棋子
     * @param row 行号，范围 [0-7]
     * @param col 列号，范围 [0-7]
     * @return 棋子指针，如果位置为空则返回 nullptr
     * 
     * 示例：获取 e4 位置的棋子
     * @code
     * Piece* piece = board.getPiece(4, 4);
     * if (piece != nullptr) {
     *     qDebug() << "Found piece:" << piece->getColorName();
     * }
     * @endcode
     */
    Piece* getPiece(int row, int col) const;

    /**
     * @brief 在指定位置放置棋子
     * @param row 行号，范围 [0-7]
     * @param col 列号，范围 [0-7]
     * @param piece 要放置的棋子指针（可以为 nullptr 以清除该位置）
     * 
     * 示例：在 d4 位置放置一个白色兵
     * @code
     * Piece* pawn = new Piece(PieceType::PAWN, PieceColor::WHITE, 4, 3);
     * board.setPiece(4, 3, pawn);
     * @endcode
     */
    void setPiece(int row, int col, Piece* piece);

    /**
     * @brief 检查给定位置是否有效
     * @param row 行号
     * @param col 列号
     * @return 如果位置在棋盘范围内（[0-7]）则返回 true
     */
    bool isValidPosition(int row, int col) const;

    /**
     * @brief 检查指定位置是否被占据
     * @param row 行号
     * @param col 列号
     * @return 如果位置有棋子则返回 true，否则返回 false
     */
    bool isOccupied(int row, int col) const;

    /**
     * @brief 检查指定位置是否有指定颜色的棋子
     * @param row 行号
     * @param col 列号
     * @param color 棋子颜色
     * @return 如果位置有指定颜色的棋子则返回 true
     */
    bool hasColoredPiece(int row, int col, PieceColor color) const;

    // ===================== 棋子移动接口 =====================

    /**
     * @brief 移动棋子（不验证合法性）
     * @param fromRow 源行号
     * @param fromCol 源列号
     * @param toRow 目标行号
     * @param toCol 目标列号
     * @return 移动是否成功
     * 
     * @note 此方法只执行物理移动，不验证移动的合法性。
     *       合法性检查由 RulesEngine 负责。
     *       如果目标位置有棋子，该棋子会被覆盖（吃掉）。
     * 
     * 示例：将 e2 的棋子移动到 e4
     * @code
     * bool success = board.movePiece(6, 4, 4, 4);
     * @endcode
     */
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief 移除指定位置的棋子（吃子操作）
     * @param row 行号
     * @param col 列号
     * @return 被移除的棋子指针，如果位置为空则返回 nullptr
     */
    Piece* removePiece(int row, int col);

    // ===================== 棋盘查询接口 =====================

    /**
     * @brief 重置棋盘到初始状态
     * 
     * 清空棋盘上所有棋子位置。
     * @note 这不会删除棋子对象本身，只是清除棋盘上的放置信息
     */
    void reset();

    /**
     * @brief 获取棋盘上的所有棋子
     * @return 棋盘上所有非空位置的棋子指针 vector
     * 
     * 示例：遍历所有棋子
     * @code
     * auto pieces = board.getAllPieces();
     * for (const auto& piece : pieces) {
     *     qDebug() << piece->getColorName() << piece->getTypeName();
     * }
     * @endcode
     */
    std::vector<Piece*> getAllPieces() const;

    /**
     * @brief 获取指定颜色的所有棋子
     * @param color 棋子颜色
     * @return 指定颜色的棋子指针 vector
     * 
     * 示例：获取所有白棋
     * @code
     * auto whitePieces = board.getPiecesByColor(PieceColor::WHITE);
     * @endcode
     */
    std::vector<Piece*> getPiecesByColor(PieceColor color) const;

    /**
     * @brief 获取指定颜色和类型的棋子
     * @param color 棋子颜色
     * @param type 棋子类型
     * @return 指定颜色和类型的棋子指针 vector
     * 
     * 示例：获取所有白棋兵
     * @code
     * auto pawns = board.getPiecesByColorAndType(
     *     PieceColor::WHITE, PieceType::PAWN);
     * @endcode
     */
    std::vector<Piece*> getPiecesByColorAndType(
        PieceColor color, PieceType type) const;

    /**
     * @brief 获取指定颜色的王
     * @param color 棋子颜色
     * @return 指定颜色的王指针，如果不存在则返回 nullptr
     * 
     * @note 正常情况下，每种颜色应该有且仅有一个王
     */
    Piece* getKing(PieceColor color) const;

    /**
     * @brief 获取棋盘的原始二维数组（仅供内部使用）
     * @return 8x8 棋子指针数组
     * 
     * @warning 这是一个低级接口，仅供内部调试和优化使用
     */
    Piece* const (*getRawBoard())[BOARD_SIZE];

private:
    // ===================== 成员变量 =====================

    /**
     * @brief 棋盘的内部表示
     * 8x8 二维数组，每个元素是棋子指针或 nullptr
     */
    Piece* m_board[BOARD_SIZE][BOARD_SIZE];
};

#endif // BOARD_H
