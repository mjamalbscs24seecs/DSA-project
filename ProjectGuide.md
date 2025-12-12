# Maze Pathfinder — Project Guide

## What this project does
- Generates grid mazes, builds a graph, and solves with BFS, DFS, and A* (Manhattan).
- CLI to pick maze size, start/goal, and algorithm; prints path, stats.
- Day 7 harness checks correctness/edge cases; Day 8 harness benchmarks performance.
- Optional SFML visualizer (if SFML is installed) to view the maze and path in a window.

## Key components
- `include/` & `src/data-structures/`: Maze, Graph, BFS, DFS, A* implementations.
- `src/Solver.cpp`: Small wrapper to run algorithms and collect timing/expansions.
- `src/main.cpp`: CLI entry point.
- `tests/day7.cpp`: Functional checks and edge cases.
- `tests/day8.cpp`: Benchmarks and CSV export.
- `src/visualize_sfml.cpp`: SFML-based viewer (optional).
- `REPORT.md`: Efficiency writeup and benchmark table.
- `CMakeLists.txt`, `build.ps1`: Build tooling.

## What’s ready
- Algorithms modularized; shared graph wiring; CLI error handling.
- Benchmarks captured at N = 100, 200, 400 (3-run averages) with Big-O summary.
- PPM export and SFML visualizer for quick visuals.

## What’s configurable
- Maze size and start/goal via CLI args.
- Algorithm selection: BFS | DFS | A*.
- PPM output file name (`--out`) and SFML visualizer (build-time flag).
- Benchmark sizes/runs: edit `tests/day8.cpp`.

## Notes for grading/demo
- For quick visuals without SFML, use `--out maze.ppm` when running the CLI.
- SFML build requires pointing CMake to your SFML install (`-DENABLE_SFML=ON -DSFML_DIR=...`).
- If start/goal are blocked by random walls, CLI forces them open; still possible no path exists (handled with a message).
- Screenshots of visualizations are collected in the docx named `visualizations`.
