#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

Maze::Maze(int size) : N(size) {
    grid.resize(N, vector<int>(N, 1)); // initially all walls
}

// Randomized DFS
void Maze::dfsMaze(int x, int y) {
    grid[x][y] = 0; // mark as open
    vector<pair<int,int>> directions = {{0,1},{1,0},{0,-1},{-1,0}}; // R,D,L,U
    shuffle(directions.begin(), directions.end(), default_random_engine(time(0)));

    for (auto [dx, dy] : directions) {
        int nx = x + dx*2; // skip 1 to leave wall between cells
        int ny = y + dy*2;
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] == 1) {
            grid[x + dx][y + dy] = 0; // remove wall
            dfsMaze(nx, ny);
        }
    }
}

void Maze::generateMaze() {
    int startX = 0, startY = 0;
    dfsMaze(startX, startY);
}

void Maze::printMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (grid[i][j] == 1 ? '#' : '.');
        cout << "\n";
    }
}

vector<vector<int>>& Maze::getGrid() { return grid; }
