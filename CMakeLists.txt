cmake_minimum_required(VERSION 3.15)
project(DSAProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core
    src/data-structures/Maze.cpp
    src/data-structures/Graph.cpp
    src/data-structures/BFS.cpp
    src/data-structures/DFS.cpp
    src/data-structures/AStar.cpp
    src/Solver.cpp
)
target_include_directories(core PUBLIC include)

add_executable(maze_solver src/main.cpp)
target_link_libraries(maze_solver core)

add_executable(day7 tests/day7.cpp)
target_link_libraries(day7 core)

add_executable(day8 tests/day8.cpp)
target_link_libraries(day8 core)
