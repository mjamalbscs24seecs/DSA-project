#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <unordered_map>
#include "Maze.h"
#include "Graph.h"

class AStar {
private:
    Maze& maze;
    Graph graph;

    struct Node {
        int x, y;
        int g, h;
        int f;
        bool operator>(const Node& other) const {
            return f > other.f;
        }
    };

    int manhattan(int x1, int y1, int x2, int y2);

    void reconstructPath(
        std::unordered_map<long long, long long>& parent,
        int ex, int ey,
        std::vector<std::pair<int,int>>& outPath
    );

    long long hash(int x, int y) {
        return (long long)x * 100000 + y;
    }

public:
    // metrics
    int expansions = 0;
    int opensPushed = 0;

    AStar(Maze& m);

    std::vector<std::pair<int,int>> run(
        std::pair<int,int> start = {0,0},
        std::pair<int,int> goal = {-1,-1}
    );
};

#endif
