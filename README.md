# 国际象棋游戏项目 (Chess Game)

## 📋 项目概述

一个基于 Qt5 开发的可扩展国际象棋游戏，具有以下特点：
- ✅ 完整的国际象棋游戏逻辑
- ✅ 可自定义棋子和棋盘贴图
- ✅ 清晰的分层架构设计
- ✅ 详细的代码注释
- ✅ VS2022 开发环境支持
- ✅ 易于扩展（AI、网络对战等）

## 🛠️ 开发环境要求

- **编译器**: Visual Studio 2022
- **Qt版本**: Qt 5.14+ (推荐 Qt 5.15)
- **C++标准**: C++17
- **构建工具**: CMake 3.16+
- **系统**: Windows 10/11

## 📁 项目结构

```
Chess/
├── src/
│   ├── core/                    # 核心游戏逻辑
│   │   ├── piece.h / piece.cpp              # 棋子类
│   │   ├── board.h / board.cpp              # 棋盘类
│   │   ├── game.h / game.cpp                # 游戏管理器
│   │   ├── move.h / move.cpp                # 移动信息
│   │   └── rules_engine.h / rules_engine.cpp # 规则引擎
│   │
│   ├── ui/                      # 用户界面层
│   │   ├── mainwindow.h / mainwindow.cpp    # 主窗口
│   │   ├── chessboard_widget.h / chessboard_widget.cpp  # 棋盘显示
│   │   ├── game_controller.h / game_controller.cpp      # 游戏控制
│   │   └── ui_resources.qrc                 # Qt资源文件
│   │
│   ├── resource/                # 资源管理
│   │   ├── resource_manager.h / resource_manager.cpp    # 资源管理器
│   │   ├── texture_loader.h / texture_loader.cpp        # 纹理加载
│   │   ├── theme_manager.h / theme_manager.cpp          # 主题管理
│   │   └── config.h / config.cpp                        # 配置管理
│   │
│   ├── utils/                   # 工具函数
│   │   ├── logger.h / logger.cpp            # 日志系统
│   │   ├── constants.h                      # 常量定义
│   │   └── helper.h / helper.cpp            # 辅助函数
│   │
│   └── main.cpp                 # 程序入口
│
├── resources/
│   ├── images/
│   │   ├── pieces/              # 棋子贴图
│   │   │   ├── white/
│   │   │   │   ├── king.png
│   │   │   │   ├── queen.png
│   │   │   │   ├── rook.png
│   │   │   │   ├── bishop.png
│   │   │   │   ├── knight.png
│   │   │   │   └── pawn.png
│   │   │   └── black/
│   │   │       └── (同上)
│   │   ├── board/               # 棋盘贴图
│   │   │   ├── board_default.png
│   │   │   └── square_dark.png
│   │   └── icons/               # 按钮图标
│   │       ├── new_game.png
│   │       ├── undo.png
│   │       └── settings.png
│   │
│   ├── themes/                  # 主题配置文件
│   │   ├── default_theme.json
│   │   ├── dark_theme.json
│   │   └── light_theme.json
│   │
│   └── resources.qrc            # Qt资源索引
│
├── CMakeLists.txt               # CMake配置
├── Chess.sln                    # VS2022解决方案
├── Chess.vcxproj                # VS2022项目文件
├── .gitignore
└── README.md
```

## 🚀 快速开始

### 1. 构建项目

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 2. 在VS2022中打开

```bash
start Chess.sln
```

### 3. 运行程序

```bash
./Release/Chess.exe
```

## 🎮 游戏功能

- ✅ 完整的国际象棋规则实现
- ✅ 移动验证和合法性检查
- ✅ 撤销功能
- ✅ 游戏状态管理（进行中、将军、将死、平局）
- ✅ 自定义棋子和棋盘贴图
- ✅ 主题切换

## 🎨 自定义贴图

### 方法1：替换资源文件

将您的贴图文件放在以下目录：
- `resources/images/pieces/white/` - 白棋贴图
- `resources/images/pieces/black/` - 黑棋贴图
- `resources/images/board/` - 棋盘贴图

### 方法2：使用API设置

```cpp
#include "resource/resource_manager.h"

ResourceManager& manager = ResourceManager::getInstance();

// 设置自定义白棋王贴图
manager.setCustomPieceTexture("white", "king", "path/to/custom_king.png");

// 设置自定义棋盘贴图
manager.setCustomBoardTexture("my_board", "path/to/custom_board.png");
```

## 🏗️ 架构设计

### 分层架构

```
┌─────────────────────────────────┐
│    UI Layer (用户界面层)         │
│  MainWindow, ChessBoardWidget   │
└────────────┬────────────────────┘
             │
┌────────────▼────────────────────┐
│   Controller Layer (控制层)      │
│    GameController                │
└────────────┬────────────────────┘
             │
┌────────────▼────────────────────┐
│   Core Layer (核心逻辑层)        │
│ Game, Board, Piece, RulesEngine  │
└────────────┬────────────────────┘
             │
┌────────────▼────────────────────┐
│  Resource Layer (资源管理层)    │
│ ResourceManager, ThemeManager   │
└─────────────────────────────────┘
```

## 🔧 可扩展设计

本项目采用模块化设计，易于添加以下功能：

1. **AI对手**
   - 创建 `AIPlayer` 基类
   - 实现不同难度的算法（EasyAI、HardAI等）

2. **网络对战**
   - 添加 `NetworkManager` 类
   - 支持局域网或在线对战

3. **棋局录制/回放**
   - 保存/加载 PGN 格式棋局
   - 实现棋局分析功能

4. **音效系统**
   - 添加 `SoundManager` 类
   - 棋子移动、吃子等音效

## 📝 代码注释规范

所有代码都采用 Doxygen 注释格式，包括：
- 类和函数的详细说明
- 参数说明
- 返回值说明
- 异常处理说明

## 📄 许可证

MIT License

## 👨‍💻 作者

yangyu

## 🤝 贡献

欢迎提交 Pull Request 或提出 Issue！
