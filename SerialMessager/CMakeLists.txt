cmake_minimum_required(VERSION 3.5.0)

project(SerialMessager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VCPKG_TARGET_TRIPLET x64-windows)
set(DCMAKE_TOOLCHAIN_FILE C:/VCpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(${DCMAKE_TOOLCHAIN_FILE})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets SerialPort REQUIRED)

set(MAIN_WINDOW_DIR main_window)

add_executable(SerialMessager WIN32
    main.cpp
    ${MAIN_WINDOW_DIR}/main_window.cpp       ${MAIN_WINDOW_DIR}/main_window.hpp   
)

target_link_libraries(SerialMessager Qt5::Widgets Qt5::SerialPort)
