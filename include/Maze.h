#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
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
    void savePPM(const vector<pair<int,int>> &path, const string &filename, int cellSize = 5) const;
};

#endif
