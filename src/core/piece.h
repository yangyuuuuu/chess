/**
 * @file piece.h
 * @brief 棋子类定义
 * @author yangyu
 * @date 2024
 * 
 * 本文件定义了棋子类，代表棋盘上的一个棋子。
 * 每个棋子有类型（兵、马、象等）、颜色（黑/白）、位置和贴图。
 */

#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QPixmap>

/**
 * @enum PieceType
 * @brief 棋子类型枚举
 * 
 * 定义了国际象棋中的所有棋子类型
 */
enum class PieceType {
    PAWN,    /**< 兵 - 基础棋子 */
    KNIGHT,  /**< 马 - 骑士 */
    BISHOP,  /**< 象 - 主教 */
    ROOK,    /**< 车 - 城堡 */
    QUEEN,   /**< 后 - 皇后 */
    KING     /**< 王 - 国王 */
};

/**
 * @enum PieceColor
 * @brief 棋子颜色枚举
 * 
 * 国际象棋中两种颜色的棋子
 */
enum class PieceColor {
    WHITE,   /**< 白棋 */
    BLACK    /**< 黑棋 */
};

/**
 * @class Piece
 * @brief 棋子类
 * 
 * 代表棋盘上的一个棋子，包含棋子的所有属性和操作。
 * 该类采用简单的数据结构设计，主要用于存储和管理棋子的状态。
 * 
 * @note 棋子的移动规则由 RulesEngine 类负责验证
 */
class Piece {
public:
    /**
     * @brief 构造函数
     * @param type 棋子类型 (PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING)
     * @param color 棋子颜色 (WHITE, BLACK)
     * @param row 初始行位置，范围 [0-7]，-1 表示未放置
     * @param col 初始列位置，范围 [0-7]，-1 表示未放置
     * 
     * 示例：创建一个在 e2 位置的白色兵
     * @code
     * Piece* pawn = new Piece(PieceType::PAWN, PieceColor::WHITE, 6, 4);
     * @endcode
     */
    Piece(PieceType type, PieceColor color, int row = -1, int col = -1);

    /**
     * @brief 析构函数
     */
    ~Piece() = default;

    // ===================== 获取器 (Getters) =====================

    /**
     * @brief 获取棋子类型
     * @return 棋子类型 (PieceType 枚举值)
     */
    PieceType getType() const { return m_type; }

    /**
     * @brief 获取棋子颜色
     * @return 棋子颜色 (PieceColor 枚举值)
     */
    PieceColor getColor() const { return m_color; }

    /**
     * @brief 获取棋子所在的行号
     * @return 行号，范围 [0-7]，-1 表示未放置
     * 
     * 棋盘坐标系说明：
     * - 行号：0 为黑棋起始行，7 为白棋起始行
     * - 列号：0 为 a 文件，7 为 h 文件
     */
    int getRow() const { return m_row; }

    /**
     * @brief 获取棋子所在的列号
     * @return 列号，范围 [0-7]，-1 表示未放置
     */
    int getColumn() const { return m_col; }

    /**
     * @brief 获取棋子贴图
     * @return 常量引用，指向棋子的 QPixmap 对象
     */
    const QPixmap& getTexture() const { return m_texture; }

    /**
     * @brief 获取棋子类型的字符串表示
     * @return 棋子类型名称 ("Pawn", "Knight", "Bishop", "Rook", "Queen", "King")
     */
    QString getTypeName() const;

    /**
     * @brief 获取棋子颜色的字符串表示
     * @return 棋子颜色名称 ("White" 或 "Black")
     */
    QString getColorName() const;

    // ===================== 设置器 (Setters) =====================

    /**
     * @brief 设置棋子的位置
     * @param row 新的行号，范围 [0-7] 或 -1 (未放置)
     * @param col 新的列号，范围 [0-7] 或 -1 (未放置)
     * 
     * 此方法用于移动棋子。不会验证移动的合法性，
     * 合法性检查由 RulesEngine 负责。
     * 
     * 示例：将棋子移动到 e4 位置
     * @code
     * piece->setPosition(4, 4);
     * @endcode
     */
    void setPosition(int row, int col);

    /**
     * @brief 设置棋子的贴图
     * @param pixmap 新的贴图对象 (QPixmap)
     * 
     * 这个接口允许玩家自定义棋子的外观。
     * 棋子贴图通常由 ResourceManager 加载和设置。
     * 
     * 示例：设置自定义棋子贴图
     * @code
     * QPixmap customTexture("path/to/custom_king.png");
     * piece->setTexture(customTexture);
     * @endcode
     */
    void setTexture(const QPixmap& pixmap);

    // ===================== 公共方法 =====================

    /**
     * @brief 检查棋子是否已放置在棋盘上
     * @return 如果棋子在棋盘上则返回 true，否则返回 false
     */
    bool isPlaced() const { return m_row >= 0 && m_col >= 0; }

    /**
     * @brief 获取棋子的标准国际象棋符号
     * @return 符号字符串 ("P", "N", "B", "R", "Q", "K")
     * 
     * 用于 PGN (Portable Game Notation) 格式
     */
    QString getFENSymbol() const;

private:
    // ===================== 成员变量 =====================

    PieceType m_type;      /**< 棋子类型 */
    PieceColor m_color;    /**< 棋子颜色 */
    int m_row;             /**< 行位置 [0-7] 或 -1 */
    int m_col;             /**< 列位置 [0-7] 或 -1 */
    QPixmap m_texture;     /**< 贴图资源 */
};

#endif // PIECE_H
