# Question 6 - Graph Representation Comparison

## Given problem

Consider the social network with the connections:

A-B, A-C, B-D, B-E, C-F, E-F

The graph is treated as an **undirected graph**.

### (a) Implement the network using

1. Adjacency Matrix
2. Adjacency List

Then perform BFS and DFS starting from vertex A.

### (b) Search operation

The program asks for a target vertex and searches for it from A using BFS
with both representations. It records the number of vertices examined and
the representation-specific checks.

Sample target: **F**

### (c) Analysis

The program compares:

- Space requirements
- Traversal behaviour
- Search/edge-checking operations
- Time complexity

## Correct representations

### Adjacency Matrix

```text
    A B C D E F
A : 0 1 1 0 0 0
B : 1 0 0 1 1 0
C : 1 0 0 0 0 1
D : 0 1 0 0 0 0
E : 0 1 0 0 0 1
F : 0 0 1 0 1 0
```

### Adjacency List

```text
A -> B C
B -> A D E
C -> A F
D -> B
E -> B F
F -> C E
```

## Traversal result from A

- BFS: A B C D E F
- DFS: A B D E F C

The same traversal order is obtained for both representations because the
neighbours are stored in the same alphabetical/order sequence.

## Search result for F

The search is performed from A using BFS.

- Adjacency Matrix: A, B and C are examined before F is discovered.
  Three vertices are examined and 18 matrix-position checks are performed.
- Adjacency List: A, B and C are examined before F is discovered.
  Three vertices are examined and 7 neighbour checks are performed.

This is a more meaningful comparison than simply scanning the vertex-label
array, because it measures how each graph representation supports a graph
search.

## Edge check for E-F

- Matrix: one direct lookup, matrix[E][F], so the operation is O(1).
- List: E has neighbours B and F, so two neighbour checks are required.

## Complexity summary

| Operation | Adjacency Matrix | Adjacency List |
|---|---|---|
| Space | O(V^2) | O(V + E) |
| BFS | O(V^2) | O(V + E) |
| DFS | O(V^2) | O(V + E) |
| Edge check | O(1) | O(degree(u)) |
| Graph search | O(V^2) worst case | O(V + E) worst case |

For V = 6 and E = 6:
- Matrix storage = 6 × 6 = 36 entries.
- Undirected adjacency-list storage contains 2E = 12 neighbour entries,
  apart from the list/vertex overhead.

## Final conclusion

For this social network, the adjacency list is the more space-efficient
representation because the graph is sparse: it stores only the existing
connections instead of all possible vertex pairs. It also gives
O(V + E) BFS/DFS traversal time, compared with O(V^2) for the matrix.

The adjacency matrix still has an important advantage: checking whether a
specific edge exists takes O(1) direct access. Therefore, the appropriate
choice depends on the operation required. For this particular sparse
social-network graph, where traversal and storage efficiency are important,
the adjacency list is suitable.

## Files

- `graph.c` - complete C source code
- `input.txt` - sample input
- `output.txt` - sample output
- `complexity_analysis.txt` - detailed complexity analysis
- `comparison_table.txt` - comparison table
- `README.md` - complete written answer and conclusion
