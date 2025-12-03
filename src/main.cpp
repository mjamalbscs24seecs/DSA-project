#include "BFS.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <Maze.h>
using namespace std;
using namespace chrono;

int main() {
    // Test case 1: 3x3
    int N=3;
    Maze maze(N);
    maze.generateMaze();
    Graph g(N);
    g.buildFromMaze(maze.getGrid());

    cout << "Maze ("<<N<<"x"<<N<<")\n";
    maze.printMaze();

    BFS bfs(g,N);
    vector<pair<int,int>> visitedOrder;
    int expansions;
    auto start = high_resolution_clock::now();
    auto path = bfs.run({0,0},{N-1,N-1},visitedOrder, expansions);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    cout << "\nBFS visited order: ";
    for(auto [x,y]: visitedOrder) cout << "("<<x<<","<<y<<") ";
    cout << "\nNumber of expansions: " << expansions;
    cout << "\nPath length: " << path.size();
    cout << "\nExecution time: " << duration << " microseconds";

    cout << "\nPath:\n";
    printPath(path, maze.getGrid());

    // Test case 2: 5x5
    N=5;
    Maze maze2(N);
    maze2.generateMaze();
    Graph g2(N);
    g2.buildFromMaze(maze2.getGrid());

    BFS bfs2(g2,N);
    visitedOrder.clear();
    start = high_resolution_clock::now();
    path = bfs2.run({0,0},{N-1,N-1},visitedOrder, expansions);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();

    cout << "\n\nMaze ("<<N<<"x"<<N<<")\n";
    maze2.printMaze();
    cout << "\nNumber of expansions: " << expansions;
    cout << "\nPath length: " << path.size();
    cout << "\nExecution time: " << duration << " microseconds\n";
    printPath(path, maze2.getGrid());

    return 0;
}