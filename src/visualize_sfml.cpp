#include <SFML/Graphics.hpp>
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

static std::string normalizeAlgo(std::string in) {
    std::string out;
    for (char c : in) {
        if (c == '*') continue;
        out.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    if (out == "A") out = "ASTAR";
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
    args.algo = normalizeAlgo(argv[6]);
    return !args.algo.empty();
}

static bool inBounds(int x, int y, int n) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

int main(int argc, char** argv) {
    CliArgs args;
    if (!parseArgs(argc, argv, args)) {
        std::cerr << "Usage: ./visualize_sfml N startX startY goalX goalY BFS|DFS|A*\n";
        return 1;
    }
    if (args.n <= 0 || !inBounds(args.sx, args.sy, args.n) || !inBounds(args.gx, args.gy, args.n)) {
        std::cerr << "Invalid inputs.\n";
        return 1;
    }

    Maze maze(args.n, args.n);
    maze.generateRandom();
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
        std::cerr << "Unknown algo. Use BFS, DFS, or A*.\n";
        return 1;
    }

    if (result.path.empty()) {
        std::cerr << "No path found in generated maze.\n";
        return 2;
    }

    int maxSide = std::max(maze.rows, maze.cols);
    int cell = std::max(2, 800 / maxSide);
    int width = maze.cols * cell;
    int height = maze.rows * cell;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u{static_cast<unsigned int>(width),
                                                       static_cast<unsigned int>(height)}),
                            "Maze Visualizer");

    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(cell), static_cast<float>(cell)));
    auto colorCell = [&](int r, int c) -> sf::Color {
        if (maze.grid[r][c] == 1) return sf::Color(30, 30, 30);
        if (r == args.sx && c == args.sy) return sf::Color(0, 180, 0);
        if (r == args.gx && c == args.gy) return sf::Color(200, 0, 0);
        return sf::Color(230, 230, 230);
    };

    // Mark path cells once so drawing stays cheap.
    std::vector<std::vector<bool>> onPath(maze.rows, std::vector<bool>(maze.cols, false));
    for (auto &p : result.path) onPath[p.first][p.second] = true;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        window.clear(sf::Color::Black);

        for (int i = 0; i < maze.rows; i++) {
            for (int j = 0; j < maze.cols; j++) {
                rect.setPosition(sf::Vector2f(static_cast<float>(j * cell), static_cast<float>(i * cell)));
                sf::Color col = colorCell(i, j);
                if (onPath[i][j] && !(i == args.sx && j == args.sy) && !(i == args.gx && j == args.gy)) {
                    col = sf::Color(30, 144, 255);
                }
                rect.setFillColor(col);
                window.draw(rect);
            }
        }

        window.display();
    }

    return 0;
}
