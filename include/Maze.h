#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Maze {
public:
    int rows, cols;
    vector<vector<int>> grid;

    Maze(int r, int c);
    void generateRandom();
    bool isOpen(int r, int c) const;
    void printMaze() const;
    void printPath(const vector<pair<int,int>> &path) const;
};

#endif
