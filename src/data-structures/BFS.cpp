#include "BFS.h"
#include <chrono>
#include <algorithm>

vector<pair<int,int>> BFS::run(pair<int,int> start, pair<int,int> goal,
                               vector<pair<int,int>> &visitedOrder,
                               int &expansions) {

    BFSQueue q;
    vector<vector<bool>> visited(N, vector<bool>(N,false));
    vector<vector<pair<int,int>>> parent(N, vector<pair<int,int>>(N, {-1,-1}));

    // Handle trivial start==goal case early
    if(start == goal){
        visitedOrder.push_back(start);
        expansions = 1;
        return {start};
    }

    q.push(start);
    visited[start.first][start.second] = true;

    expansions = 0;
    bool goalReached = false;

    while(!q.empty()){
        auto [x,y] = q.pop();
        visitedOrder.push_back({x,y});
        expansions++;

        if(x==goal.first && y==goal.second){
            goalReached = true;
            break;
        }

        for(auto [nx,ny] : g.neighbors(x,y)){
            if(!visited[nx][ny]){
                visited[nx][ny]=true;
                parent[nx][ny]={x,y};
                q.push({nx,ny});
            }
        }
    }

    if(!goalReached) return {};

    // Reconstruct path
    vector<pair<int,int>> path;
    pair<int,int> cur = goal;
    while(cur.first!=-1){
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return path;
}
