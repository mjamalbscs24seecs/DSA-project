#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <utility>
#include <string>
#include "Maze.h"
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"

struct SearchResult {
    std::vector<std::pair<int,int>> path;
    int expansions = 0;
    double milliseconds = 0.0;
};

class Solver {
public:
    Solver(Maze& maze, Graph& graph);

    SearchResult runBFS(std::pair<int,int> start, std::pair<int,int> goal);
    SearchResult runDFS(std::pair<int,int> start, std::pair<int,int> goal);
    SearchResult runAStar(std::pair<int,int> start, std::pair<int,int> goal);

private:
    Maze& maze;
    Graph& graph;
};

#endif
