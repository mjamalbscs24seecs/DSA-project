#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <utility>
#include <Graph.h>

class AStar {
private:
    Graph g;
    int N;

    int heuristic(int x, int y, int gx, int gy);

public:
    AStar(const Graph& graph, int n);

    std::vector<std::pair<int,int>> run(
        std::pair<int,int> start,
        std::pair<int,int> goal,
        std::vector<std::pair<int,int>>& visitedOrder,
        int& expansions,
        std::vector<int>& fValuesLog
    );
};

#endif
