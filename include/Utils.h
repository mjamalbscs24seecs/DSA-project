#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <iostream>
using namespace std;

void printPath(vector<pair<int,int>> path, vector<vector<int>> grid){
    for (auto [x,y] : path) grid[x][y] = 2;
    for (auto &row : grid) {
        for (auto cell : row) {
            if (cell == 1) cout << "#";
            else if (cell == 2) cout << "*";
            else cout << ".";
        }
        cout << "\n";
    }
}

#endif
