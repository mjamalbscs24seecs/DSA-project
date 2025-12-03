#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
using namespace std;

class Graph {
private:
    int N; // maze size
    vector<vector<pair<int,int>>> adj; // adjacency list of cells
public:
    Graph(int size);
    void buildFromMaze(vector<vector<int>>& grid);
    vector<pair<int,int>>& neighbors(int x, int y);
    vector<vector<pair<int,int>>>& getAdjacencyList();
};

#endif
