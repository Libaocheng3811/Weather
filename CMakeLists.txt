cmake_minimum_required(VERSION 3.16)

project(Weather VERSION 1.0.0)

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
    message(STATUS "Qt5_DIR: ${Qt5_DIR}")
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
# target_compile_options命令用于给指定的目标（这里是你的项目 ${PROJECT_NAME}）添加编译选项。
# INTERFACE 关键字意味着这些选项不仅会应用于当前目标，如果这个目标是一个库被其他目标链接时，这些选项也会传递给链接它的目标
# 但PRIVATE 更适合可执行文件
# "/source-charset:utf-8": 这个是 MSVC 特有的编译选项。告诉 MSVC 编译器，你的源代码文件 (.cpp, .h 等) 本身是使用 UTF-8 编码保存的。
# "/execution-charset:utf-8": 这个是 MSVC 特有的编译选项。告诉 MSVC 编译器，你的程序在运行时所使用的字符集是 UTF-8。
if(MSVC) # 仅对 MSVC 编译器，因为这些标志是 MSVC 特有的
    target_compile_options(${PROJECT_NAME} PRIVATE "/source-charset:utf-8" "/execution-charset:utf-8")
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
# QNX 是一个嵌入式实时操作系统
if(QNX)
    set(INSTALL_BIN_DIR "/tmp/${PROJECT_NAME}/bin")
elseif(UNIX AND NOT ANDROID AND NOT APPLE) # unix:!android 通常指 Linux/BSD 等，不包括 macOS
    set(INSTALL_BIN_DIR "/opt/${PROJECT_NAME}/bin")
endif()

# --- 安装规则 ---
# 定义安装目标。这些文件会被复制到 CMAKE_INSTALL_PREFIX 指定的目录下。
# CPack 会打包 CMAKE_INSTALL_PREFIX 下的内容。

# install() 命令定义哪些文件（你的可执行文件、必要的第三方 DLL、资源文件等）应该被“安装”到一个临时的安装目录结构中。
# windeployqt： 在构建完成后，对这个临时安装目录中的可执行文件运行 windeployqt，以自动部署所有 Qt 相关的依赖。
# CPack 配置： 在 CMakeLists.txt 中添加 CPack 的配置，告诉它如何将这个临时安装目录的内容打包成一个安装程序（例如 NSIS 的 .exe 安装包）。

# 安装可执行文件到 <prefix>/bin 目录
# CMake 会使用一个默认的 CMAKE_INSTALL_PREFIX (Windows 上通常是 C:/Program Files (x86)/YourProjectName)。
# 可以在命令行构建时通过 -DCMAKE_INSTALL_PREFIX 设置自定义路径，如cmake -DCMAKE_INSTALL_PREFIX=F:/MyInstallDir ..
# 但并不推荐在 CMakeLists.txt 中设置，因为这会破坏用户可自定义安装路径的能力
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin  # 可执行文件
        # LIBRARY DESTINATION lib  # 如果是库
        # ARCHIVE DESTINATION lib/static # 如果是静态库
        COMPONENT Applications    # 将其归类为一个组件，方便 CPack 管理
)

set(JSON_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/citycode-2019-08-23.json")

if(EXISTS "${JSON_CONFIG_FILE}")
    install(FILES "${JSON_CONFIG_FILE}"
            DESTINATION bin  # 安装到 <prefix>/bin 目录，与可执行文件一起
            COMPONENT Applications # 可以与应用程序归为同一个组件
            # RENAME config_renamed.json # 可选：如果想在安装时重命名文件
    )
    message(STATUS "Will install JSON config file: ${JSON_CONFIG_FILE} to bin/")
else()
    message(WARNING "JSON config file not found at ${JSON_CONFIG_FILE}. It will not be installed.")
endif()

# 如果你有其他需要随程序一起分发的非代码文件（例如配置文件、文档、第三方DLL）
# 你需要为它们也添加 install() 命令。
# 例如，安装一个 README 文件到安装目录的根：
# install(FILES README.md DESTINATION . COMPONENT Documentation)

# 例如，安装一个第三方 DLL 到 bin 目录：
# install(FILES path/to/your/third_party.dll DESTINATION bin COMPONENT RuntimeLibraries)

# 确保 .ui 文件生成的头文件能被找到 (与打包不直接相关，但对编译重要)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR} # 添加当前构建目录到包含路径
)
# --- 如果是 GUI 应用 (通常 Qt Widgets 应用都是)，确保 Windows 上的行为正确 ---
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()

# --- CPack 配置 (通常放在 CMakeLists.txt 的末尾) ---
# 仅当当前是 Windows 平台时执行
if(WIN32)
    set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}") # 使用 project() 中定义的版本
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple weather application")
    set(CPACK_PACKAGE_VENDOR "baocheng Li")
    set(CPACK_PACKAGE_CONTACT "libaocheng1234@gmail.com")

    # 选择 NSIS 作为 Windows 安装包生成器
    set(CPACK_GENERATOR "NSIS")

    set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME} ${PROJECT_VERSION}") # 安装程序窗口标题
    set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME}") # 在“添加/删除程序”中显示的名称
    set(CPACK_NSIS_PUBLISHER "${CPACK_PACKAGE_VENDOR}")
    set(CPACK_NSIS_URL_INFO_ABOUT "your-website.com") # “关于”链接
    set(CPACK_NSIS_HELP_LINK "your-help-page.com")    # “帮助”链接
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${PROJECT_NAME}.exe") # 开始菜单快捷方式指向的程序
    set(CPACK_NSIS_CREATE_DESKTOP_LINK "${PROJECT_NAME}")          # 创建桌面快捷方式的名称
    set(CPACK_NSIS_MENU_LINKS "bin\\\\${PROJECT_NAME}.exe" "${PROJECT_NAME}") # 创建开始菜单快捷方式

    # 允许用户修改安装目录
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_MODIFY_PATH OFF) # 通常不建议安装程序修改系统 PATH

    get_filename_component(QT_INSTALL_PREFIX "${Qt5_DIR}/../../../" ABSOLUTE) # 退回到 Qt 安装根目录
    set(QT_BIN_DIR "${QT_INSTALL_PREFIX}/bin")
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
    message(STATUS "WINDEPLOYQT_EXECUTABLE is: ${WINDEPLOYQT_EXECUTABLE}")

    if(NOT WINDEPLOYQT_EXECUTABLE)
        message(WARNING "windeployqt not found. Qt deployment might be incomplete. Searched in ${QT_BIN_DIR}")
    else()
        message(STATUS "Found windeployqt: ${WINDEPLOYQT_EXECUTABLE}")
        # 添加一个自定义的安装脚本，在所有文件安装完成后运行 windeployqt
        # CMAKE_INSTALL_PREFIX 是 CPack 使用的安装根目录
        # 我们对 CMAKE_INSTALL_PREFIX/bin/YourProjectName.exe 运行 windeployqt
        # 注意：这个脚本会在 `cmake --install` 时运行，也会在 `cpack` 生成包之前运行（如果cpack内部调用了install）
        install(CODE "
            message(STATUS \"Running windeployqt on ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe\")
            execute_process(
                COMMAND \"${WINDEPLOYQT_EXECUTABLE}\"
                    --compiler-runtime        # 包含MinGW运行时
                    --no-translations         # 根据需要调整
                    --no-opengl-sw
                    --dir \"${CMAKE_INSTALL_PREFIX}/bin\"  # 指定输出目录为安装的bin目录
                    \"${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.exe\"
                RESULT_VARIABLE result
            )
            if(NOT result EQUAL 0)
                message(FATAL_ERROR \"windeployqt failed with $${result}\")
            endif()
            message(STATUS \"windeployqt finished.\")
        " COMPONENT Applications) # 确保它与你的可执行文件属于同一个组件
    endif()

    # 包含 CPack 模块以启用打包功能
    include(CPack)
endif ()