# Design Notes

## State
A state is represented as `vector<vector<int>>`, where each inner vector represents one tube.

## Search
Breadth-First Search (BFS) is used because each valid pour is one move. BFS explores states by increasing move count, so the first solved state found has a minimum number of moves.

## State history
Each `State` stores its parent state index and the source/destination tube of the move that created it. This allows the solution path to be reconstructed after reaching the goal.

## Visited states
A vector of previously seen states is used to avoid processing duplicate states.

## Complexity
Let S be the number of reachable states, N the number of tubes, and C the tube capacity.

- Each state tries O(N^2) source/destination pairs.
- Checking a move and comparing a state are bounded by O(C) and O(N*C), respectively.
- The simple vector-based visited check can take O(S*N*C) in the worst case.
- Memory is O(S*N*C) for stored states and visited states, plus the BFS queue.

The practical running time depends strongly on the number of reachable puzzle states.
