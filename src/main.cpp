#include <iostream>
#include <vector>
#include "../include/Maze.h"
#include "../include/Graph.h"
#include "../include/DS.h"

using namespace std;

int main() {
    int N = 11;
    Maze maze(N);
    maze.generateMaze();
    maze.printMaze();

    // ---------- Build Graph ----------
    Graph g(N);
    g.buildFromMaze(maze.getGrid());
    cout << "\nGraph built. Neighbors of (0,0): ";
    for(auto [x,y] : g.neighbors(0,0)) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    // ---------- Test BFSQueue ----------
    BFSQueue q;
    q.push({0,0});
    auto q_front = q.pop();
    cout << "BFSQueue front: (" << q_front.first << "," << q_front.second << ")\n";

    // ---------- Test DFSStack ----------
    DFSStack s;
    s.push({0,0});
    auto s_top = s.pop();
    cout << "DFSStack top: (" << s_top.first << "," << s_top.second << ")\n";

    // ---------- Test MinHeap ----------
    MinHeap h;
    h.push({0,0,5}); // f = 5
    h.push({1,1,3}); // f = 3
    Node n = h.pop();
    cout << "MinHeap top: (" << n.x << "," << n.y << ") f=" << n.f << "\n";

    return 0;
}
