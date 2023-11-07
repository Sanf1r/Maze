cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3 -Wall -Wextra -Werror -std=c++17 -pedantic)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Maze
        main.cc
        View/view.cc
        View/view.h
        View/view.ui
        View/mazefield.h
        View/mazefield.cc
        Controller/controller.h
        Model/model.h
        Model/model.cc
        Model/data.h
)

target_link_libraries(Maze PRIVATE Qt6::Widgets)
