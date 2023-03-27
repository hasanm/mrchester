cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD_11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



project(MrChester VERSION 1.0 LANGUAGES CXX)

configure_file(MrChesterConfig.h.in MrChesterConfig.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED )

add_executable(MrChester
        main.cpp
        mainwindow.cpp
        DrawableImage.cpp
        graphicwindow.cpp
        layoutitem.cpp
        dialog.cpp
)

target_include_directories(MrChester PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${OpenCV_INCLUDE_DIRS}")


target_link_libraries(MrChester Qt5::Widgets "${OpenCV_LIBS}")
