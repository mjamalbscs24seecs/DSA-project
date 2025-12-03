#include "Graph.h"

Graph::Graph(int size) : N(size) {
    adj.resize(N*N); // flatten 2D maze into 1D indices
}

// Helper to convert 2D (x,y) -> 1D index
inline int idx(int x, int y, int N) {
    return x*N + y;
}

void Graph::buildFromMaze(vector<vector<int>>& grid) {
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(grid[i][j]==0) { // only open cells
                vector<pair<int,int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
                for(auto [dx,dy]: dirs){
                    int ni=i+dx, nj=j+dy;
                    if(ni>=0 && ni<N && nj>=0 && nj<N && grid[ni][nj]==0){
                        adj[idx(i,j,N)].push_back({ni,nj});
                    }
                }
            }
        }
    }
}

vector<pair<int,int>>& Graph::neighbors(int x, int y) {
    return adj[idx(x,y,N)];
}

vector<vector<pair<int,int>>>& Graph::getAdjacencyList() {
    return adj;
}
