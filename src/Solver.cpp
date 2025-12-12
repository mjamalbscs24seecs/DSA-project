#include "Solver.h"
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using ms = std::chrono::duration<double, std::milli>;

Solver::Solver(Maze& m, Graph& g) : maze(m), graph(g) {}

// Each run builds a fresh search object but reuses the shared graph topology.
SearchResult Solver::runBFS(std::pair<int,int> start, std::pair<int,int> goal) {
    BFS bfs(graph, maze.rows);
    std::vector<std::pair<int,int>> visited;
    int expansions = 0;

    auto t0 = Clock::now();
    auto path = bfs.run(start, goal, visited, expansions);
    auto dt = ms(Clock::now() - t0).count();

    return {path, expansions, dt};
}

SearchResult Solver::runDFS(std::pair<int,int> start, std::pair<int,int> goal) {
    DFS dfs(graph, maze.rows);
    std::vector<std::pair<int,int>> visited;
    int expansions = 0;

    auto t0 = Clock::now();
    auto path = dfs.run(start, goal, visited, expansions);
    auto dt = ms(Clock::now() - t0).count();

    return {path, expansions, dt};
}

SearchResult Solver::runAStar(std::pair<int,int> start, std::pair<int,int> goal) {
    AStar astar(maze, graph);

    auto t0 = Clock::now();
    auto path = astar.run(start, goal);
    auto dt = ms(Clock::now() - t0).count();

    return {path, astar.expansions, dt};
}
