#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>
using namespace std;

class Maze {
private:
    int N;
    vector<vector<int>> grid;
    void dfsMaze(int x, int y); // recursive backtracking helper

public:
    Maze(int size);             // constructor
    void generateMaze();        // generate random maze
    void printMaze();           // ASCII print
    vector<vector<int>>& getGrid(); // getter for utilities
};

#endif
