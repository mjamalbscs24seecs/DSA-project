# How to Run

## Quick build (CLI only)

```
g++ -std=c++17 -Iinclude src/main.cpp src/Solver.cpp src/data-structures/Maze.cpp src/data-structures/Graph.cpp src/data-structures/BFS.cpp src/data-structures/DFS.cpp src/data-structures/AStar.cpp -o maze_solver.exe
```

## Run the solver

```
.\maze_solver.exe N startX startY goalX goalY --algo BFS|DFS|A* [--out maze.ppm]
```

- `--out` writes a PPM image with the path (no extra libs needed).
- Examples:
  - `.\maze_solver.exe 10 0 0 9 9 --algo "BFS" --out maze.ppm`
  - `.\maze_solver.exe 20 0 0 19 19 --algo "A*"`

## CMake build (all targets)

```
cmake -S . -B build
cmake --build build
```

Executables land in `build/`:

- `maze_solver` (CLI)
- `day7` (edge/correctness checks)
- `day8` (benchmarks, writes `day8_results.csv`)

PowerShell helper: `.\build.ps1`

## SFML visualizer (optional)

Requires SFML dev libs installed.

```
cmake -G "MinGW Makefiles" -S . -B build-mingw -DENABLE_SFML=ON -DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML" -DCMAKE_CXX_COMPILER=g++
cmake --build build-mingw
```

Run:

```
.\build-mingw\visualize_sfml.exe N startX startY goalX goalY A*
```

Copy SFML DLLs next to the exe (or add SFML `bin` to PATH) if Windows reports missing DLLs.

## Benchmarks

```
g++ -std=c++17 -Iinclude tests/day8.cpp src/data-structures/Maze.cpp src/data-structures/Graph.cpp src/data-structures/BFS.cpp src/data-structures/DFS.cpp src/data-structures/AStar.cpp src/Solver.cpp -o day8.exe
.\day8.exe
```

Outputs to console and `day8_results.csv`. Adjust sizes/runs in `tests/day8.cpp`.
