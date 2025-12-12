#include <iostream>
#include "Maze.h"
#include "Graph.h"
#include "DFS.h"
#include "AStar.h"

int main() {
    // Create a maze
    Maze maze(10, 10);
    maze.generateRandom();
    
    std::cout << "Maze (" << maze.rows << "x" << maze.cols << ")\n";
    maze.printMaze();

    // Build graph representation once for graph-based searches
    Graph graph(maze.rows);
    graph.buildFromMaze(maze.grid);

    // -------------------------
    // DFS TEST
    // -------------------------
    std::cout << "\n=== DFS TEST ===\n";
    DFS dfs(graph, maze.rows);
    vector<pair<int,int>> dfsVisited;
    int dfsExpansions = 0;
    auto dfsPath = dfs.run({0,0}, {maze.rows - 1, maze.cols - 1}, dfsVisited, dfsExpansions);
    maze.printPath(dfsPath);

    // -------------------------
    // A* TEST
    // -------------------------
    std::cout << "\n=== A* TEST ===\n";
    AStar astar(maze);
    auto aPath = astar.run();
    maze.printPath(aPath);

    return 0;
}
