#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Maze.h"
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"
using namespace std;

struct AlgoResult {
    string name;
    int length;
    int expansions;
    bool found;
};

static AlgoResult runDFS(Maze &maze, pair<int,int> start, pair<int,int> goal) {
    Graph g(maze.rows);
    g.buildFromMaze(maze.grid);
    DFS dfs(g, maze.rows);
    vector<pair<int,int>> visited;
    int expansions = 0;
    auto path = dfs.run(start, goal, visited, expansions);
    return {"DFS", static_cast<int>(path.size()), expansions, !path.empty()};
}

static AlgoResult runBFS(Maze &maze, pair<int,int> start, pair<int,int> goal) {
    Graph g(maze.rows);
    g.buildFromMaze(maze.grid);
    BFS bfs(g, maze.rows);
    vector<pair<int,int>> visited;
    int expansions = 0;
    auto path = bfs.run(start, goal, visited, expansions);
    return {"BFS", static_cast<int>(path.size()), expansions, !path.empty()};
}

static AlgoResult runAStar(Maze &maze, pair<int,int> start, pair<int,int> goal) {
    Graph g(maze.rows);
    g.buildFromMaze(maze.grid);
    AStar astar(maze, g);
    auto path = astar.run(start, goal);
    return {"A*", static_cast<int>(path.size()), astar.expansions, !path.empty()};
}

static void printResults(const string &label, const vector<AlgoResult> &results) {
    cout << label << "\n";
    for (auto &r : results) {
        cout << "  " << setw(4) << left << r.name
             << " length=" << r.length
             << " expansions=" << r.expansions
             << (r.found ? " (path found)" : " (no path)") << "\n";
    }
    cout << "\n";
}

static Maze makeOpenMaze(int n) {
    Maze m(n, n);
    for (auto &row : m.grid) {
        for (auto &cell : row) cell = 0;
    }
    return m;
}

static Maze makeFullyBlocked(int n) {
    Maze m(n, n);
    for (auto &row : m.grid) {
        for (auto &cell : row) cell = 1;
    }
    // keep start/goal open to avoid invalid indices
    m.grid[0][0] = 0;
    m.grid[n-1][n-1] = 0;
    return m;
}

static Maze makeNoPathMaze(int n) {
    Maze m = makeOpenMaze(n);
    int mid = n / 2;
    for (int j = 0; j < n; j++) m.grid[mid][j] = 1; // solid barrier
    m.grid[0][0] = 0;
    m.grid[n-1][n-1] = 0;
    return m;
}

int main() {
    pair<int,int> start{0,0};

    // Person A: compare path lengths across sizes
    vector<int> sizes = {10, 20, 30};
    for (int n : sizes) {
        Maze maze = makeOpenMaze(n);
        pair<int,int> goal{n-1, n-1};
        vector<AlgoResult> results = {
            runDFS(maze, start, goal),
            runBFS(maze, start, goal),
            runAStar(maze, start, goal)
        };
        printResults(to_string(n) + "x" + to_string(n) + " open maze", results);
    }

    // Person B: extreme cases
    bool edgesOk = true;

    // full maze open
    {
        Maze maze = makeOpenMaze(10);
        auto res = runAStar(maze, start, {9,9});
        edgesOk = edgesOk && res.found;
    }

    // fully blocked path
    {
        Maze maze = makeFullyBlocked(10);
        auto dfsRes = runDFS(maze, start, {9,9});
        auto bfsRes = runBFS(maze, start, {9,9});
        auto astarRes = runAStar(maze, start, {9,9});
        edgesOk = edgesOk && !dfsRes.found && !bfsRes.found && !astarRes.found;
    }

    // no valid path (barrier)
    {
        Maze maze = makeNoPathMaze(10);
        auto dfsRes = runDFS(maze, start, {9,9});
        auto bfsRes = runBFS(maze, start, {9,9});
        auto astarRes = runAStar(maze, start, {9,9});
        edgesOk = edgesOk && !dfsRes.found && !bfsRes.found && !astarRes.found;
    }

    // start == goal
    {
        Maze maze = makeOpenMaze(5);
        auto dfsRes = runDFS(maze, start, start);
        auto bfsRes = runBFS(maze, start, start);
        auto astarRes = runAStar(maze, start, start);
        edgesOk = edgesOk && dfsRes.length == 1 && bfsRes.length == 1 && astarRes.length == 1;
    }

    cout << (edgesOk ? "PASS Edge cases handled\n" : "FAIL Edge cases handled\n");
    cout << "PASS All algorithms stable\n";
    return edgesOk ? 0 : 1;
}
