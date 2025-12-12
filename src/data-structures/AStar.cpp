#include "AStar.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <limits>

AStar::AStar(Maze& m) : maze(m), graph(m.rows) {
    graph.buildFromMaze(maze.grid);
}

int AStar::manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void AStar::reconstructPath(
    std::unordered_map<long long, long long>& parent,
    int ex, int ey,
    std::vector<std::pair<int,int>>& outPath
) {
    long long curr = hash(ex, ey);

    while (parent.count(curr)) {
        int x = curr / 100000;
        int y = curr % 100000;
        outPath.push_back({x, y});
        curr = parent[curr];
    }

    std::reverse(outPath.begin(), outPath.end());
}

std::vector<std::pair<int,int>> AStar::run(
    std::pair<int,int> start,
    std::pair<int,int> goal
) {
    if (goal.first == -1) {
        goal = {maze.rows - 1, maze.cols - 1};
    }

    int sx = start.first, sy = start.second;
    int gx = goal.first, gy = goal.second;

    std::vector<std::vector<int>> gCost(
        maze.rows,
        std::vector<int>(maze.cols, std::numeric_limits<int>::max())
    );

    std::priority_queue<
        Node,
        std::vector<Node>,
        std::greater<Node>
    > pq;

    std::unordered_map<long long, long long> parent;
    std::vector<std::vector<bool>> closed(
        maze.rows, std::vector<bool>(maze.cols, false)
    );

    gCost[sx][sy] = 0;
    pq.push({sx, sy, 0, manhattan(sx, sy, gx, gy), manhattan(sx, sy, gx, gy)});
    opensPushed++;

    expansions = 0;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        int x = curr.x;
        int y = curr.y;

        if (closed[x][y]) continue;
        closed[x][y] = true;
        expansions++;

        if (x == gx && y == gy) {
            std::vector<std::pair<int,int>> path;
            reconstructPath(parent, gx, gy, path);
            return path;
        }

        for (auto& nb : graph.neighbors(x, y)) {
            int nx = nb.first;
            int ny = nb.second;

            if (maze.grid[nx][ny] == 1) continue;
            if (closed[nx][ny]) continue;

            int tentative_g = gCost[x][y] + 1;

            if (tentative_g < gCost[nx][ny]) {
                gCost[nx][ny] = tentative_g;
                parent[hash(nx, ny)] = hash(x, y);

                int h = manhattan(nx, ny, gx, gy);
                int f = tentative_g + h;

                pq.push({nx, ny, tentative_g, h, f});
                opensPushed++;

                // debug print
                // std::cout << "PUSH (" << nx << "," << ny << ") f=" << f << "\n";
            }
        }
    }

    return {};
}
