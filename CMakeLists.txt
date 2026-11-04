cmake_minimum_required(VERSION 4.3)
project(CISC220_Final)

set(CMAKE_CXX_STANDARD 14)

add_executable(CISC220_Final
        main.cpp
        game.cpp
        Levels/Level1_Maze.cpp
        Levels/Level2_Stack.cpp
        Levels/Level3_HashMap.cpp
        Levels/Level5_Graph.cpp
        Levels/Level4_LinkedLists.cpp
)