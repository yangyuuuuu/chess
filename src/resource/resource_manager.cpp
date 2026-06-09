/**
 * @file resource_manager.cpp
 * @brief 资源管理器实现
 * @author yangyu
 * @date 2024
 */

#include "resource_manager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

/**
 * @brief 获取资源管理器单例
 */
ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

/**
 * @brief 资源管理器构造函数
 */
ResourceManager::ResourceManager()
{
}

/**
 * @brief 初始化资源管理器
 */
bool ResourceManager::initialize(const QString& resourcePath)
{
    m_resourcePath = resourcePath;
    
    // 验证资源路径是否存在
    QDir resourceDir(m_resourcePath);
    if (!resourceDir.exists()) {
        return false;
    }
    
    return true;
}

/**
 * @brief 加载棋子贴图
 */
QPixmap ResourceManager::getPieceTexture(const QString& color, const QString& type)
{
    QString key = color + "_" + type;
    
    // 先检查缓存
    QPixmap cached = getTextureFromCache(key);
    if (!cached.isNull()) {
        return cached;
    }
    
    // 从文件加载
    QString path = QString("%1/images/pieces/%2/%3.png")
        .arg(m_resourcePath, color, type);
    
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        cacheTexture(key, pixmap);
    }
    
    return pixmap;
}

/**
 * @brief 设置自定义棋子贴图
 */
bool ResourceManager::setCustomPieceTexture(const QString& color, const QString& type, 
                                            const QString& path)
{
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        return false;
    }
    
    QString key = color + "_" + type;
    cacheTexture(key, pixmap);
    
    return true;
}

/**
 * @brief 获取棋盘贴图
 */
QPixmap ResourceManager::getBoardTexture(const QString& boardName)
{
    QString key = "board_" + boardName;
    
    // 先检查缓存
    QPixmap cached = getTextureFromCache(key);
    if (!cached.isNull()) {
        return cached;
    }
    
    // 从文件加载
    QString path = QString("%1/images/board/%2.png")
        .arg(m_resourcePath, boardName);
    
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        cacheTexture(key, pixmap);
    }
    
    return pixmap;
}

/**
 * @brief 设置自定义棋盘贴图
 */
bool ResourceManager::setCustomBoardTexture(const QString& boardName, const QString& path)
{
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        return false;
    }
    
    QString key = "board_" + boardName;
    cacheTexture(key, pixmap);
    
    return true;
}

/**
 * @brief 加载主题配置
 */
bool ResourceManager::loadTheme(const QString& themeName)
{
    QString themePath = QString("%1/themes/%2_theme.json")
        .arg(m_resourcePath, themeName);
    
    QFile file(themePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (!doc.isObject()) {
        return false;
    }
    
    m_currentTheme = doc.object();
    return true;
}

/**
 * @brief 获取主题配置值
 */
QString ResourceManager::getThemeValue(const QString& key) const
{
    if (m_currentTheme.contains(key)) {
        return m_currentTheme.value(key).toString();
    }
    return QString();
}

/**
 * @brief 缓存贴图
 */
void ResourceManager::cacheTexture(const QString& key, const QPixmap& pixmap)
{
    m_textureCache.insert(key, pixmap);
}

/**
 * @brief 从缓存获取贴图
 */
QPixmap ResourceManager::getTextureFromCache(const QString& key) const
{
    if (m_textureCache.contains(key)) {
        return m_textureCache.value(key);
    }
    return QPixmap();
}
