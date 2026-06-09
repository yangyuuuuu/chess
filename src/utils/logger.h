/**
 * @file logger.h
 * @brief 日志系统
 * @author yangyu
 * @date 2024
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <memory>

/**
 * @enum LogLevel
 * @brief 日志级别枚举
 */
enum class LogLevel {
    DEBUG,     /**< 调试信息 */
    INFO,      /**< 一般信息 */
    WARNING,   /**< 警告 */
    ERROR,     /**< 错误 */
    CRITICAL   /**< 严重错误 */
};

/**
 * @class Logger
 * @brief 日志系统
 * 
 * 负责整个游戏的日志输出。
 * 采用单例模式确保全局唯一的日志器具。
 * 
 * 示例使用：
 * @code
 * Logger::getInstance().init("game.log");
 * Logger::getInstance().info("Game started");
 * Logger::getInstance().warning("Invalid move");
 * Logger::getInstance().error("Resource not found");
 * @endcode
 */
class Logger {
public:
    /**
     * @brief 获取日志系统单例
     * @return Logger 单例的引用
     */
    static Logger& getInstance();

    /**
     * @brief 初始化日志文件
     * @param filename 日志文件路径
     * @return 是否初始化成功
     */
    bool init(const QString& filename);

    /**
     * @brief 打印调试信息
     * @param message 消息内容
     */
    void debug(const QString& message);

    /**
     * @brief 打印一般信息
     * @param message 消息内容
     */
    void info(const QString& message);

    /**
     * @brief 打印警告信息
     * @param message 消息内容
     */
    void warning(const QString& message);

    /**
     * @brief 打印错误信息
     * @param message 消息内容
     */
    void error(const QString& message);

    /**
     * @brief 打印严重错误
     * @param message 消息内容
     */
    void critical(const QString& message);

    /**
     * @brief 晓库模式化写入
     * @param message 消息内容
     */
    void log(LogLevel level, const QString& message);

private:
    // 私有构造函数 - 单例模式
    Logger();

    // 禁止复制
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    QFile m_logFile;        /**< 日志文件 */
    QTextStream m_stream;   /**< 文本流 */

    /**
     * @brief 获取日志级别的字符串
     * @param level 日志级别
     * @return 级别名称
     */
    QString getLevelString(LogLevel level) const;
};

#endif // LOGGER_H
