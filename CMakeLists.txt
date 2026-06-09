cmake_minimum_required(VERSION 3.16)
project(Chess CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 配置
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 找 Qt
find_package(Qt5 COMPONENTS 
    Core 
    Gui 
    Widgets 
    REQUIRED
)

# 源文件
set(SOURCES
    src/main.cpp
    
    # Core 核心层
    src/core/piece.h
    src/core/piece.cpp
    src/core/board.h
    src/core/board.cpp
    src/core/move.h
    src/core/game.h
    src/core/game.cpp
    
    # Resource 资源层
    src/resource/resource_manager.h
    
    # Utils 工具层
    src/utils/logger.h
    src/utils/logger.cpp
)

# 创建可执行程序
add_executable(Chess ${SOURCES})

# 链接 Qt 库
target_link_libraries(Chess
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# MSVC 编译器优化
if(MSVC)
    # 直接使用 Unicode
    add_definitions(-DUNICODE -D_UNICODE)
    # 获取最优的性能
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob2 /Oi /Ot")
    endif()
endif()
