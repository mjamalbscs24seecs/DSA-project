# DSA-project

## Big-O Analysis
- BFS: O(V + E)
- DFS: O(V + E)
- A*: O(E log V) with a binary heap (heuristic quality influences constants)

## Build and run
Using CMake:
1. `cmake -S . -B build`
2. `cmake --build build`
3. Run CLI: `./build/maze_solver N startX startY goalX goalY --algo BFS|DFS|A*`

Quick build on Windows PowerShell: `.\build.ps1`

Other executables:
- `./build/day7` runs Day 7 pathfinding checks.
- `./build/day8` runs Day 8 benchmarking (outputs `day8_results.csv`).
- Optional SFML visualizer (requires SFML dev libs on your system): `cmake -DENABLE_SFML=ON -S . -B build && cmake --build build`, then run `./build/visualize_sfml N startX startY goalX goalY BFS|DFS|A*`.
