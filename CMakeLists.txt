cmake_minimum_required(VERSION 3.10)

project(Weather)

# 启用Qt自动处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32 AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
    set(CMAKE_NATIVE_PATH_ENCODING UTF-8)
endif()

# 设置 C++ 标准 (根据 .pro 文件的 CONFIG += c++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # 通常推荐关闭编译器特定扩展

find_package(Qt5 COMPONENTS Core Widgets Gui Network REQUIRED)
if(Qt5_FOUND)
    message(STATUS "Found Qt5, version ${Qt5_VERSION}")
else()
    message(FATAL_ERROR "Qt5 not found")
endif()

# --- 项目源文件 ---
set(PROJECT_SOURCES
        Weather.cpp
        main.cpp
        WeatherUtils.cpp
)

set(PROJECT_HEADERS
        Weather.h
        WeatherTool.h
        WeatherUtils.h
)

set(PROJECT_UI_FILES
        Weather.ui
)

# --- Qt 资源文件 ---
set(PROJECT_RESOURCES
        icons/icons.qrc
        images/images.qrc
        weatherIcons/weatypeico.qrc
)

# --- 可执行文件目标 ---
add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UI_FILES}
        ${PROJECT_RESOURCES}
)

# 为 C++ 项目设置源文件编码和执行编码，以确保编译器能正确处理包含非 ASCII 字符（例如中文字符）的源代码，并且程序在运行时能正确显示这些字符。
# CMAKE_CXX_COMPILER_ID: CMake 内置变量，表示当前 C++ 编译器的标识符（如 "GNU" for GCC, "Clang" for Clang, "MSVC" for Visual C++）。
# target_compile_options命令用于给指定的目标（这里是你的项目 ${PROJECT_NAME}）添加编译选项。INTERFACE 关键字意味着这些选项不仅会应用于当前目标，如果这个目标是一个库被其他目标链接时，这些选项也会传递给链接它的目标
# "/source-charset:utf-8": 这个是 MSVC 特有的编译选项。告诉 MSVC 编译器，你的源代码文件 (.cpp, .h 等) 本身是使用 UTF-8 编码保存的。
# "/execution-charset:utf-8": 这个是 MSVC 特有的编译选项。告诉 MSVC 编译器，你的程序在运行时所使用的字符集是 UTF-8。
if(MSVC) # 仅对 MSVC 编译器，因为这些标志是 MSVC 特有的
    target_compile_options(${PROJECT_NAME} INTERFACE "/source-charset:utf-8" "/execution-charset:utf-8")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} INTERFACE "-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()
# MATCHES "GNU|Clang": 正则表达式匹配，检查编译器 ID 是否是 "GNU" 或 "Clang"。或者Mingw，因为它也是GCC的变种。
# "-finput-charset=UTF-8": 告诉编译器，输入的源代码文件是使用 UTF-8 编码保存的。
# "-fexec-charset=UTF-8": 告诉编译器，程序在运行时所使用的字符集是 UTF-8。

# --- 链接 Qt 库 ---
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Network
        Qt5::Widgets
)

# CMake 中的 install 命令更灵活
if(QNX)
    set(INSTALL_BIN_DIR "/tmp/${PROJECT_NAME}/bin")
elseif(UNIX AND NOT ANDROID AND NOT APPLE) # unix:!android 通常指 Linux/BSD 等，不包括 macOS
    set(INSTALL_BIN_DIR "/opt/${PROJECT_NAME}/bin")
endif()

if(INSTALL_BIN_DIR)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION ${INSTALL_BIN_DIR} # 安装可执行文件
            # 如果是库，还会有 LIBRARY 和 ARCHIVE
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR} # 添加当前构建目录到包含路径
)
# --- 如果是 GUI 应用 (通常 Qt Widgets 应用都是)，确保 Windows 上的行为正确 ---
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()