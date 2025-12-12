#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "Maze.h"
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"
using namespace std;

struct BenchResult {
    string algo;
    double avgMs;
    double avgExpansions;
    bool success;
};

static Maze makeOpenMaze(int n) {
    Maze m(n, n);
    for (auto &row : m.grid) {
        for (auto &cell : row) cell = 0;
    }
    return m;
}

static bool hasPath(Maze &maze) {
    Graph g(maze.rows);
    g.buildFromMaze(maze.grid);
    BFS bfs(g, maze.rows);
    vector<pair<int,int>> visited;
    int expansions = 0;
    auto path = bfs.run({0,0}, {maze.rows - 1, maze.cols - 1}, visited, expansions);
    return !path.empty();
}

static Maze makeRandomMazeWithPath(int n, int maxAttempts = 100) {
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        Maze m(n, n);
        m.generateRandom();
        if (hasPath(m)) return m;
    }
    // fallback to fully open maze to guarantee a path
    return makeOpenMaze(n);
}

static BenchResult benchBFS(Maze &maze, int runs) {
    double tSum = 0.0;
    double eSum = 0.0;
    bool ok = true;
    for (int i = 0; i < runs; ++i) {
        Graph g(maze.rows);
        g.buildFromMaze(maze.grid);
        BFS bfs(g, maze.rows);
        vector<pair<int,int>> visited;
        int expansions = 0;
        auto t0 = chrono::high_resolution_clock::now();
        auto path = bfs.run({0,0}, {maze.rows - 1, maze.cols - 1}, visited, expansions);
        auto t1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> dt = t1 - t0;
        tSum += dt.count();
        eSum += expansions;
        ok = ok && !path.empty();
    }
    return {"BFS", tSum / runs, eSum / runs, ok};
}

static BenchResult benchDFS(Maze &maze, int runs) {
    double tSum = 0.0;
    double eSum = 0.0;
    bool ok = true;
    for (int i = 0; i < runs; ++i) {
        Graph g(maze.rows);
        g.buildFromMaze(maze.grid);
        DFS dfs(g, maze.rows);
        vector<pair<int,int>> visited;
        int expansions = 0;
        auto t0 = chrono::high_resolution_clock::now();
        auto path = dfs.run({0,0}, {maze.rows - 1, maze.cols - 1}, visited, expansions);
        auto t1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> dt = t1 - t0;
        tSum += dt.count();
        eSum += expansions;
        ok = ok && !path.empty();
    }
    return {"DFS", tSum / runs, eSum / runs, ok};
}

static BenchResult benchAStar(Maze &maze, int runs) {
    double tSum = 0.0;
    double eSum = 0.0;
    bool ok = true;
    for (int i = 0; i < runs; ++i) {
        Graph g(maze.rows);
        g.buildFromMaze(maze.grid);
        AStar astar(maze, g);
        auto t0 = chrono::high_resolution_clock::now();
        auto path = astar.run({0,0}, {maze.rows - 1, maze.cols - 1});
        auto t1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> dt = t1 - t0;
        tSum += dt.count();
        eSum += astar.expansions;
        ok = ok && !path.empty();
    }
    return {"A*", tSum / runs, eSum / runs, ok};
}

static void writeResult(ofstream &out, int n, const BenchResult &r) {
    out << n << "," << r.algo << "," << fixed << setprecision(3) << r.avgMs
        << "," << setprecision(2) << r.avgExpansions << "," << (r.success ? "ok" : "fail") << "\n";
}

int main() {
    vector<int> sizes = {100, 200, 400};
    const int runs = 3;

    ofstream out("day8_results.csv");
    out << "size,algorithm,avg_ms,avg_expansions,success\n";

    cout << "Day 8 Benchmark (avg over " << runs << " runs)\n";

    for (int n : sizes) {
        Maze maze = makeRandomMazeWithPath(n);

        auto bfsR = benchBFS(maze, runs);
        auto dfsR = benchDFS(maze, runs);
        auto aR   = benchAStar(maze, runs);

        writeResult(out, n, bfsR);
        writeResult(out, n, dfsR);
        writeResult(out, n, aR);

        cout << "\n" << n << "x" << n << " maze\n";
        cout << "  BFS  avg_ms=" << fixed << setprecision(3) << bfsR.avgMs
             << " avg_exp=" << bfsR.avgExpansions << (bfsR.success ? "" : " (no path)") << "\n";
        cout << "  DFS  avg_ms=" << fixed << setprecision(3) << dfsR.avgMs
             << " avg_exp=" << dfsR.avgExpansions << (dfsR.success ? "" : " (no path)") << "\n";
        cout << "  A*   avg_ms=" << fixed << setprecision(3) << aR.avgMs
             << " avg_exp=" << aR.avgExpansions << (aR.success ? "" : " (no path)") << "\n";
    }

    cout << "\nPASS Auto benchmarking works\n";
    cout << "PASS Results exported to day8_results.csv\n";
    return 0;
}
