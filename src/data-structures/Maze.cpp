#include "Maze.h"
#include <cstdlib>

Maze::Maze(int r, int c) : rows(r), cols(c) {
    grid = vector<vector<int>>(rows, vector<int>(cols, 0));
}

void Maze::generateRandom() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 0 = open, 1 = wall
            grid[i][j] = (rand() % 100 < 25) ? 1 : 0;
        }
    }
    grid[0][0] = 0;
    grid[rows - 1][cols - 1] = 0;
}

bool Maze::isOpen(int r, int c) const {
    return r >= 0 && c >= 0 && r < rows && c < cols && grid[r][c] == 0;
}

void Maze::printMaze() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << (grid[i][j] == 0 ? "." : "#") << " ";
        }
        cout << "\n";
    }
}

void Maze::printPath(const vector<pair<int,int>>& path) const {
    vector<vector<char>> disp(rows, vector<char>(cols, '.'));

    for (auto &p : path) disp[p.first][p.second] = '*';

    disp[0][0] = 'S';
    disp[rows-1][cols-1] = 'G';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) cout << "# ";
            else cout << disp[i][j] << " ";
        }
        cout << "\n";
    }
}
