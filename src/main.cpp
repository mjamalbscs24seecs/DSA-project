#include <iostream>
#include <vector>
#include "../include/Maze.h"

using namespace std;

// Check if cell is valid
bool isValidCell(int x, int y, int N, vector<vector<int>>& grid) {
    return x >= 0 && x < N && y >= 0 && y < N && grid[x][y] == 0;
}

// Get valid neighbors
vector<pair<int,int>> neighbors(int x, int y, int N, vector<vector<int>>& grid) {
    vector<pair<int,int>> result;
    vector<pair<int,int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    for (auto [dx,dy] : dirs) {

        int nx = x + dx, ny = y + dy;
        if (isValidCell(nx, ny, N, grid))
            result.push_back({nx, ny});
    }
    return result;
}

// Print path on maze
void printPath(vector<pair<int,int>> path, vector<vector<int>> grid) {
    for (auto [x,y] : path) grid[x][y] = 2; // mark path
    for (auto &row : grid) {
        for (auto cell : row) {
            if (cell == 1) cout << "#";
            else if (cell == 2) cout << "*";
            else cout << ".";
        }
        cout << "\n";
    }
}

int main() {
    int N = 11; // odd numbers recommended for DFS maze
    Maze maze(N);
    maze.generateMaze();
    maze.printMaze();

    // Test neighbors function
    auto grid = maze.getGrid();
    auto neigh = neighbors(0,0,N,grid);
    cout << "\nNeighbors of (0,0): ";
    for (auto [x,y] : neigh) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    return 0;
}
