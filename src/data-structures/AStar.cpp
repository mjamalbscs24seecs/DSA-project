#include "AStar.h"
#include <cmath>
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

AStar::AStar(const Graph& graph, int n) : g(graph), N(n) {}

int AStar::heuristic(int x, int y, int gx, int gy) {
    return abs(x - gx) + abs(y - gy);     // Manhattan distance
}

vector<pair<int,int>> AStar::run(
    pair<int,int> start,
    pair<int,int> goal,
    vector<pair<int,int>>& visitedOrder,
    int& expansions,
    vector<int>& fValuesLog
) {
    expansions = 0;
    visitedOrder.clear();
    fValuesLog.clear();

    int total = N * N;

    vector<int> gCost(total, INT_MAX);
    vector<bool> closed(total, false);
    vector<int> parent(total, -1);

    auto encode = [&](int x, int y){ return x*N + y; };
    auto decode = [&](int id){ return make_pair(id/N, id%N); };

    int s = encode(start.first, start.second);
    int t = encode(goal.first, goal.second);

    gCost[s] = 0;

    // priority queue: (f, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int sx = start.first, sy = start.second;
    int gx = goal.first, gy = goal.second;

    pq.push({ heuristic(sx,sy,gx,gy), s });

    while(!pq.empty()) {
        auto [f, u] = pq.top();
        pq.pop();

        if (closed[u]) continue;
        closed[u] = true;

        expansions++;
        visitedOrder.push_back(decode(u));
        fValuesLog.push_back(f);

        if (u == t) {
            // reconstruct path
            vector<pair<int,int>> path;
            while(u != -1) {
                path.push_back(decode(u));
                u = parent[u];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        auto neighbors = g.getAdjList()[u];
        for (auto [vx, vy] : neighbors) {
            int v = encode(vx,vy);
            if (closed[v]) continue;

            int newCost = gCost[u] + 1; // uniform edges

            if (newCost < gCost[v]) {
                gCost[v] = newCost;
                parent[v] = u;

                int h = heuristic(vx, vy, gx, gy);
                pq.push({ newCost + h, v });
            }
        }
    }

    return {};
}
