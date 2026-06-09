/**
 * @file game.h
 * @brief 游戏管理器类定义
 * @author yangyu
 * @date 2024
 * 
 * 本文件定义了游戏类，负责整个游戏流程的管理。
 */

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "move.h"
#include <vector>
#include <memory>

/**
 * @enum GameState
 * @brief 游戏状态枚举
 */
enum class GameState {
    IDLE,       /**< 闲置状态，等待新游戏开始 */
    PLAYING,    /**< 游戏进行中 */
    CHECK,      /**< 当前玩家被将军 */
    CHECKMATE,  /**< 游戏结束 - 被将死 */
    STALEMATE,  /**< 游戏结束 - 僵局 */
    DRAW,       /**< 游戏结束 - 平局 */
    GAME_OVER   /**< 游戏结束 */
};

/**
 * @class Game
 * @brief 游戏管理器类
 * 
 * 负责整个游戏的流程管理，包括：
 * - 游戏状态的维护
 * - 回合制的管理
 * - 移动的验证和执行
 * - 游戏规则的检查（将军、将死等）
 * - 移动历史的记录
 * 
 * 使用单例模式确保全局唯一的游戏实例。
 */
class Game {
public:
    /**
     * @brief 获取游戏单例实例
     * @return Game 对象的引用
     */
    static Game& getInstance();

    /**
     * @brief 构造函数
     */
    explicit Game();

    /**
     * @brief 析构函数
     */
    ~Game();

    /**
     * @brief 删除复制构造函数
     */
    Game(const Game&) = delete;

    /**
     * @brief 删除赋值操作符
     */
    Game& operator=(const Game&) = delete;

    // ===================== 游戏控制接口 =====================

    /**
     * @brief 开始新游戏
     * 
     * 初始化棋盘、重置游戏状态、清空移动历史。
     * 游戏状态变为 PLAYING，白棋先手。
     */
    void startNewGame();

    /**
     * @brief 尝试执行一个棋子移动
     * @param fromRow 源行号 [0-7]
     * @param fromCol 源列号 [0-7]
     * @param toRow 目标行号 [0-7]
     * @param toCol 目标列号 [0-7]
     * @return 移动是否成功执行
     * 
     * 此方法会验证移动的合法性：
     * - 源位置有棋子
     * - 棋子属于当前玩家
     * - 移动符合棋子的移动规则
     * - 移动不会让自己的王被将军
     * 
     * 如果移动合法，会：
     * - 更新棋盘状态
     * - 记录移动历史
     * - 切换玩家
     * - 更新游戏状态（检查将军、将死等）
     */
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief 撤销上一步移动
     * @return 撤销是否成功
     * 
     * 恢复棋盘到上一个状态，包括：
     * - 恢复被吃的棋子
     * - 恢复棋子位置
     * - 切换玩家
     * - 更新游戏状态
     * 
     * @note 如果没有可以撤销的移动，返回 false
     */
    bool undoMove();

    /**
     * @brief 重新开始游戏
     * 
     * 等价于 startNewGame()，用于玩家点击"重新开始"按钮
     */
    void restartGame();

    /**
     * @brief 认输当前游戏
     * 
     * 当前玩家认输，对方获胜。
     * 游戏状态变为 GAME_OVER。
     */
    void resign();

    // ===================== 游戏状态查询接口 =====================

    /**
     * @brief 获取当前游戏状态
     * @return 游戏状态 (GameState 枚举值)
     */
    GameState getGameState() const { return m_state; }

    /**
     * @brief 获取当前玩家的棋子颜色
     * @return 当前玩家的棋子颜色
     * 
     * 示例：
     * @code
     * if (game.getCurrentPlayer() == PieceColor::WHITE) {
     *     qDebug() << "White's turn";
     * }
     * @endcode
     */
    PieceColor getCurrentPlayer() const { return m_currentPlayer; }

    /**
     * @brief 检查游戏是否已结束
     * @return 如果游戏结束则返回 true
     */
    bool isGameOver() const;

    /**
     * @brief 获取游戏获胜者
     * @return 获胜者的棋子颜色
     * 
     * @note 只有在游戏结束时才有意义
     */
    PieceColor getWinner() const { return m_winner; }

    /**
     * @brief 获取游戏获胜方式的描述
     * @return 获胜方式的文本描述
     */
    QString getGameEndReason() const;

    // ===================== 棋盘访问接口 =====================

    /**
     * @brief 获取棋盘对象的引用
     * @return Board 对象的非 const 引用
     * 
     * 这允许外部代码直接访问棋盘。
     * @warning 请谨慎使用，避免绕过游戏规则
     */
    Board& getBoard() { return m_board; }

    /**
     * @brief 获取棋盘对象的常量引用
     * @return Board 对象的 const 引用
     */
    const Board& getConstBoard() const { return m_board; }

    // ===================== 移动历史接口 =====================

    /**
     * @brief 获取移动历史
     * @return 所有移动的 vector（只读）
     */
    const std::vector<MoveRecord>& getMoveHistory() const {
        return m_moveHistory;
    }

    /**
     * @brief 获取移动历史数量
     * @return 已执行的移动数
     */
    size_t getMoveCount() const { return m_moveHistory.size(); }

    /**
     * @brief 获取最后一个移动
     * @return 最后一个移动的常量引用，如果没有移动则返回无效移动
     */
    const MoveRecord& getLastMove() const;

    // ===================== 合法移动查询接口 =====================

    /**
     * @brief 获取指定位置棋子的所有合法移动
     * @param row 行号
     * @param col 列号
     * @return 合法移动的 vector
     * 
     * 返回的移动已经过所有验证，包括将军检查。
     */
    std::vector<Move> getLegalMoves(int row, int col) const;

    /**
     * @brief 检查移动是否合法
     * @param move 要检查的移动
     * @return 移动是否合法
     */
    bool isMoveLegal(const Move& move) const;

    // ===================== 游戏规则检查接口 =====================

    /**
     * @brief 检查指定颜色的玩家是否被将军
     * @param color 棋子颜色
     * @return 是否被将军
     */
    bool isInCheck(PieceColor color) const;

    /**
     * @brief 检查指定颜色的玩家是否被将死
     * @param color 棋子颜色
     * @return 是否被将死
     */
    bool isCheckmate(PieceColor color) const;

    /**
     * @brief 检查游戏是否是僵局
     * @param color 棋子颜色
     * @return 是否是僵局
     */
    bool isStalemate(PieceColor color) const;

    /**
     * @brief 检查指定棋子的移动是否会导致自己被将军
     * @param piece 棋子指针
     * @param move 移动
     * @return 移动是否会导致自己被将军
     */
    bool wouldMoveExposeKing(Piece* piece, const Move& move) const;

private:
    // ===================== 成员变量 =====================

    Board m_board;                          /**< 棋盘对象 */
    GameState m_state;                      /**< 当前游戏状态 */
    PieceColor m_currentPlayer;             /**< 当前玩家 */
    PieceColor m_winner;                    /**< 获胜者 */
    std::vector<MoveRecord> m_moveHistory;  /**< 移动历史 */
    std::vector<std::unique_ptr<Piece>> m_pieces;  /**< 所有棋子对象 */

    // ===================== 私有方法 =====================

    /**
     * @brief 初始化棋盘到标准开局位置
     */
    void initializeBoard();

    /**
     * @brief 切换到下一个玩家
     */
    void switchPlayer();

    /**
     * @brief 更新游戏状态
     * 检查当前玩家是否被将军、将死等
     */
    void updateGameState();

    /**
     * @brief 检查国王是否被攻击
     * @param kingColor 国王的颜色
     * @param kingRow 国王的行位置
     * @param kingCol 国王的列位置
     * @return 国王是否被攻击
     */
    bool isKingUnderAttack(PieceColor kingColor, int kingRow, int kingCol) const;

    /**
     * @brief 检查某个位置是否被指定颜色的棋子攻击
     * @param targetRow 目标行
     * @param targetCol 目标列
     * @param attackerColor 攻击方颜色
     * @return 该位置是否被攻击
     */
    bool isPositionUnderAttack(int targetRow, int targetCol, PieceColor attackerColor) const;
};

#endif // GAME_H
