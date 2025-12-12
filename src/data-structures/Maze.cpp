#include "Maze.h"
#include <cstdlib>
#include <fstream>
#include <unordered_set>

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

// Quick PPM export for lightweight 2D visualization without extra deps.
void Maze::savePPM(const vector<pair<int,int>> &path, const string &filename, int cellSize) const {
    auto hashPair = [](const pair<int,int>& p) {
        return (static_cast<long long>(p.first) << 32) ^ static_cast<unsigned long long>(p.second);
    };
    unordered_set<long long> pathCells;
    pathCells.reserve(path.size() * 2);
    for (auto &p : path) pathCells.insert(hashPair(p));

    int width = cols * cellSize;
    int height = rows * cellSize;

    ofstream out(filename, ios::binary);
    if (!out) return;

    out << "P6\n" << width << " " << height << "\n255\n";

    auto writePixel = [&](unsigned char r, unsigned char g, unsigned char b){
        out.put(static_cast<char>(r));
        out.put(static_cast<char>(g));
        out.put(static_cast<char>(b));
    };

    for (int i = 0; i < rows; i++) {
        for (int sy = 0; sy < cellSize; sy++) {
            for (int j = 0; j < cols; j++) {
                bool isWall = grid[i][j] == 1;
                bool isStart = (i == 0 && j == 0);
                bool isGoal = (i == rows - 1 && j == cols - 1);
                bool onPath = pathCells.count(hashPair({i,j})) > 0;

                unsigned char r = 255, g = 255, b = 255; // open = white
                if (isWall) { r = g = b = 0; }
                else if (isStart) { r = 0; g = 200; b = 0; }
                else if (isGoal) { r = 200; g = 0; b = 0; }
                else if (onPath) { r = 30; g = 144; b = 255; } // path = blueish

                for (int sx = 0; sx < cellSize; sx++) {
                    writePixel(r, g, b);
                }
            }
        }
    }
}
