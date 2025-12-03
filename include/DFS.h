#ifndef DFS_H
#define DFS_H

#include "Graph.h"
#include "DS.h"
#include <vector>
#include <utility>
using namespace std;

class DFS {
private:
    Graph &g;
    int N;
public:
    DFS(Graph &graph, int size) : g(graph), N(size) {}

    vector<pair<int,int>> run(pair<int,int> start, pair<int,int> goal,
                              vector<pair<int,int>> &visitedOrder,
                              int &expansions);
};

#endif
