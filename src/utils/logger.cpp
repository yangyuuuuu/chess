/**
 * @file logger.cpp
 * @brief 日志系统实现
 * @author yangyu
 * @date 2024
 */

#include "logger.h"
#include <QDateTime>
#include <iostream>

/**
 * @brief 获取日志单例
 */
Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

/**
 * @brief Logger 构造函数
 */
Logger::Logger()
{
}

/**
 * @brief 初始化日志文件
 */
bool Logger::init(const QString& filename)
{
    m_logFile.setFileName(filename);
    if (!m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Failed to open log file: " << filename.toStdString() << std::endl;
        return false;
    }
    m_stream.setDevice(&m_logFile);
    return true;
}

/**
 * @brief 打印调试信息
 */
void Logger::debug(const QString& message)
{
    log(LogLevel::DEBUG, message);
}

/**
 * @brief 打印一般信息
 */
void Logger::info(const QString& message)
{
    log(LogLevel::INFO, message);
}

/**
 * @brief 打印警告
 */
void Logger::warning(const QString& message)
{
    log(LogLevel::WARNING, message);
}

/**
 * @brief 打印错误
 */
void Logger::error(const QString& message)
{
    log(LogLevel::ERROR, message);
}

/**
 * @brief 打印严重错误
 */
void Logger::critical(const QString& message)
{
    log(LogLevel::CRITICAL, message);
}

/**
 * @brief 统一日志接口
 */
void Logger::log(LogLevel level, const QString& message)
{
    QString levelStr = getLevelString(level);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logMessage = QString("[%1] %2 - %3").arg(timestamp, levelStr, message);

    // 输出到控制台
    std::cout << logMessage.toStdString() << std::endl;

    // 输出到文件
    if (m_logFile.isOpen()) {
        m_stream << logMessage << "\n";
        m_stream.flush();
    }
}

/**
 * @brief 获取日志级别字符串
 */
QString Logger::getLevelString(LogLevel level) const
{
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}
