cmake_minimum_required(VERSION 3.16)

project(2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
    ./include
)

set(SOURCE_FILES
   ./src/game_2048.cpp
   ./src/main.cpp
)

add_executable(Game_2048 ${SOURCE_FILES})
