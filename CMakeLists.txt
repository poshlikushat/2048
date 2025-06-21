cmake_minimum_required(VERSION 3.15)
project(Game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio)

add_executable(Game src/main.cpp
        src/Tile.cpp
        src/Renderer.cpp
        src/Board.cpp
        src/GameController.cpp
        include/Board.h
        include/GameController.h
        include/Renderer.h
        include/Tile.h)

file(COPY ${CMAKE_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(Game
        PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
)
