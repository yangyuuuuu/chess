/**
 * @file main.cpp
 * @brief 程序入口点
 * @author yangyu
 * @date 2024
 * 
 * 这是国际象棋游戏的程序入口，负责：
 * - 初始化 Qt 应用程序
 * - 创建主窗口
 * - 启动事件循环
 */

#include <QApplication>
#include "ui/mainwindow.h"
#include "resource/resource_manager.h"
#include "utils/logger.h"

/**
 * @brief 程序主函数
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 程序退出码
 */
int main(int argc, char *argv[])
{
    // 创建 Qt 应用程序
    QApplication app(argc, argv);

    // 初始化日志系统
    Logger::getInstance().init("chess.log");
    Logger::getInstance().info("Chess game starting...");

    // 初始化资源管理器
    ResourceManager& resourceMgr = ResourceManager::getInstance();
    QString resourcePath = QApplication::applicationDirPath() + "/resources";
    if (!resourceMgr.initialize(resourcePath)) {
        Logger::getInstance().error("Failed to initialize resource manager");
        return -1;
    }
    Logger::getInstance().info("Resource manager initialized");

    // 加载默认主题
    if (!resourceMgr.loadTheme("default")) {
        Logger::getInstance().warning("Failed to load default theme");
    }

    // 创建主窗口
    MainWindow window;
    window.show();

    Logger::getInstance().info("Main window created and shown");

    // 启动事件循环
    return app.exec();
}
