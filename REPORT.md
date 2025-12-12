# Maze Pathfinder Efficiency Report

## Big-O recap
- BFS: O(V + E)
- DFS: O(V + E)
- A*: O(E log V) with binary-heap open list (heuristic quality affects constants, not order)

## Benchmark setup
- Grid mazes of size N x N with random walls; regenerated until a valid path exists.
- Algorithms: BFS, DFS, A* (Manhattan heuristic).
- Metrics: average wall-clock time (ms) and average expansions over 3 runs.
- Hardware/compile: g++ -std=c++17 (MinGW) on local Windows machine.

## Results (averaged over 3 runs)

| Size (N x N) | Algorithm | Avg time (ms) | Avg expansions |
|--------------|-----------|---------------|----------------|
| 100 | BFS | 2.065 | 7,506 |
| 100 | DFS | 0.317 | 323 |
| 100 | A*  | 2.474 | 2,443 |
| 200 | BFS | 9.234 | 29,716 |
| 200 | DFS | 0.708 | 584 |
| 200 | A*  | 11.841 | 11,469 |
| 400 | BFS | 35.554 | 119,503 |
| 400 | DFS | 2.312 | 1,431 |
| 400 | A*  | 15.724 | 12,439 |

## Notes
- DFS expands fewer nodes on these random mazes because it can reach the goal quickly via any valid depth-first route; BFS and A* do more systematic exploration, hence higher expansions.
- A* reduces expansions compared to BFS, but its priority queue adds overhead in time.
- All runs used open grids with guaranteed connectivity; tighter/wall-heavy mazes will shift expansions and times upward. Try larger N or more runs by editing `tests/day8.cpp`.
