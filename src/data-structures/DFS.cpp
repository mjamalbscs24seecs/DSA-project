#include "DFS.h"
#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;

vector<pair<int,int>> DFS::run(pair<int,int> start, pair<int,int> goal,
                               vector<pair<int,int>> &visitedOrder,
                               int &expansions) {

    DFSStack s;
    vector<vector<bool>> visited(N, vector<bool>(N,false));
    vector<vector<pair<int,int>>> parent(N, vector<pair<int,int>>(N, {-1,-1}));

    // Handle trivial start==goal case early
    if(start == goal){
        visitedOrder.push_back(start);
        expansions = 1;
        return {start};
    }

    s.push(start);
    parent[start.first][start.second] = {-1,-1}; // start has no parent
    expansions = 0;

    while(!s.empty()){
        auto [x,y] = s.pop();

        if(visited[x][y]) continue; // skip if already visited
        visited[x][y] = true;
        visitedOrder.push_back({x,y});
        expansions++;

        if(x==goal.first && y==goal.second) break;

        // Push neighbors in reverse order for stack DFS
        auto neigh = g.neighbors(x,y);
        for(auto it = neigh.rbegin(); it != neigh.rend(); ++it){
            auto [nx,ny] = *it;
            if(!visited[nx][ny] && parent[nx][ny].first==-1){ 
                // parent not yet set
                parent[nx][ny] = {x,y};
                s.push({nx,ny});
            }
        }
    }

    // Reconstruct path from goal to start
    vector<pair<int,int>> path;
    pair<int,int> cur = goal;
    if(parent[cur.first][cur.second].first == -1){
        cout << "\nDFS Warning: No path found!\n";
        return path;
    }
    while(cur.first != -1){
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return path;
}
