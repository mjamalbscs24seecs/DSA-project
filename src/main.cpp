#include "DFS.h"
#include "BFS.h"
#include "Maze.h"
#include "Graph.h"
#include "DS.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    int N = 10;
    Maze maze(N);
    maze.generateMaze();
    Graph g(N);
    g.buildFromMaze(maze.getGrid());

    cout << "Maze ("<<N<<"x"<<N<<")\n";
    maze.printMaze();

    DFS dfs(g,N);
    vector<pair<int,int>> visitedOrder;
    int expansions;

    auto start = high_resolution_clock::now();
    auto path = dfs.run({0,0},{N-1,N-1},visitedOrder, expansions);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    cout << "\nDFS visited order: ";
    for(auto [x,y]: visitedOrder) cout << "("<<x<<","<<y<<") ";
    cout << "\nNumber of expansions: " << expansions;
    cout << "\nPath length: " << path.size();
    cout << "\nExecution time: " << duration << " microseconds";

    cout << "\nPath:\n";
    printPath(path, maze.getGrid());

    return 0;
}