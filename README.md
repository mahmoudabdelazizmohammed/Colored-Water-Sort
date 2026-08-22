# Colored Water Sort Solver

C++ console project for solving the Colored Water Sort puzzle using Breadth-First Search (BFS).

## Student
- Name: Mahmoud Abdelaziz Mohammed
- ID: 24p0485

## Project Requirements Covered
- Read N tubes and capacity C.
- Represent the puzzle using vectors.
- Generate valid pouring moves.
- Avoid repeated states.
- Use BFS to find a minimum-move solution.
- Print the solution moves and final state.
- Report when no solution exists.

## Build
Use a C++ compiler with C++17 support:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp -o water_sort
```

## Run
```bash
./water_sort < sample_inputs/example_A.txt
```

## Sample Tests
- `sample_inputs/example_A.txt` — official solvable example.
- `sample_inputs/example_B_no_solution.txt` — official no-solution example.
- `sample_inputs/test_C_one_move.txt` — additional test.

## Notes
The implementation follows the project examples and uses a simple BFS state-space search. The recorded presentation is not included because it is optional according to the instructor's instruction.
