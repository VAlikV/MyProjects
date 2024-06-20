cmake_minimum_required(VERSION 3.1.0)

project(First_ver VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VCPKG_TARGET_TRIPLET x64-windows)
set(DCMAKE_TOOLCHAIN_FILE C:/VCpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(${DCMAKE_TOOLCHAIN_FILE})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

add_executable(First_ver WIN32
    main.cpp
#    mainwindow.cpp      mainwindow.hpp
    UDPclient.cpp       UDPclient.hpp
)

target_link_libraries(First_ver Qt5::Widgets Qt5::Network)