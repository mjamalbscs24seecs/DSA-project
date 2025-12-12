#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Maze.h"
#include "Graph.h"
#include "Solver.h"

struct CliArgs {
    int n{};
    int sx{}, sy{}, gx{}, gy{};
    std::string algo;
};

static void printUsage() {
    std::cerr << "Usage: ./maze_solver N startX startY goalX goalY --algo BFS|DFS|A*\n";
}

static std::string normalizeAlgo(std::string in) {
    std::string out;
    for (char c : in) {
        if (c == '*') continue;
        out.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    return out;
}

static bool parseArgs(int argc, char** argv, CliArgs &args) {
    if (argc < 7) return false;
    try {
        args.n  = std::stoi(argv[1]);
        args.sx = std::stoi(argv[2]);
        args.sy = std::stoi(argv[3]);
        args.gx = std::stoi(argv[4]);
        args.gy = std::stoi(argv[5]);
    } catch (...) {
        return false;
    }

    if (argc >= 8 && std::string(argv[6]) == "--algo") {
        args.algo = normalizeAlgo(argv[7]);
    } else {
        args.algo = normalizeAlgo(argv[6]);
    }
    return true;
}

static bool inBounds(int x, int y, int n) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

int main(int argc, char** argv) {
    CliArgs args;
    if (!parseArgs(argc, argv, args)) {
        printUsage();
        return 1;
    }

    // Basic sanity checks before building anything expensive.
    if (args.n <= 0) {
        std::cerr << "Error: N must be positive.\n";
        return 1;
    }
    if (!inBounds(args.sx, args.sy, args.n) || !inBounds(args.gx, args.gy, args.n)) {
        std::cerr << "Error: start/goal must be inside the grid.\n";
        return 1;
    }

    Maze maze(args.n, args.n);
    maze.generateRandom();
    // Keep the requested start/goal cells open.
    maze.grid[args.sx][args.sy] = 0;
    maze.grid[args.gx][args.gy] = 0;

    Graph graph(args.n);
    graph.buildFromMaze(maze.grid);
    Solver solver(maze, graph);

    SearchResult result;
    if (args.algo == "BFS") {
        result = solver.runBFS({args.sx, args.sy}, {args.gx, args.gy});
    } else if (args.algo == "DFS") {
        result = solver.runDFS({args.sx, args.sy}, {args.gx, args.gy});
    } else if (args.algo == "ASTAR") {
        result = solver.runAStar({args.sx, args.sy}, {args.gx, args.gy});
    } else {
        std::cerr << "Error: unknown algorithm. Use BFS, DFS, or A*.\n";
        return 1;
    }

    if (result.path.empty()) {
        std::cerr << "No path found for the generated maze.\n";
        return 2;
    }

    std::cout << "Maze (" << maze.rows << "x" << maze.cols << ")\n";
    maze.printMaze();

    std::cout << "\nAlgorithm: " << (args.algo == "ASTAR" ? "A*" : args.algo)
              << "\nPath length: " << result.path.size()
              << "\nExpansions: " << result.expansions
              << "\nTime (ms): " << result.milliseconds << "\n\n";

    maze.printPath(result.path);
    return 0;
}
