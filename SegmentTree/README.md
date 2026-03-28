# Segment Tree Solution

This repository contains a segment tree implementation for solving a range update and range sum query problem.

## Problem

Given an array `A` of `n` integers and `q` queries, there are two types of operations:

1. `1 l r` — replace `A[i]` with `(i - l + 1) * A[l]` for each index `i` in the range `[l, r]`.
2. `2 l r` — compute the sum of `A[l]` through `A[r]`.

The output is the sum of answers for all type `2` queries, modulo `10^9 + 7`.

## Implementation

The code in `main (3).cpp` uses a segment tree with lazy propagation to support both updates and queries efficiently.

### Key ideas

- A segment tree stores the sum of each segment of the array.
- Lazy propagation delays updates to children nodes until they are needed.
- The update operation sets a range to values that form an arithmetic progression based on the starting value `A[l]`.
- Using arithmetic progression formulas avoids iterating over each element in the range.

### Data structures

- `vector<ll> seg` — stores segment sums for nodes of the tree.
- `vector<pair<ll,ll>> lazy` — stores lazy update metadata for each node. Each entry contains:
  - `base`: the multiplier used for the range update
  - `L`: the left boundary index for the arithmetic progression formula

### Functions

- `build(idx, l, r, A)`
  - Recursively builds the segment tree from the initial array.
- `apply(idx, l, r, base, L)`
  - Applies a lazy range update to a node.
  - Computes the sum of the arithmetic progression for segment `[l, r]`.
- `push(idx, l, r)`
  - Propagates pending lazy updates from a parent node to its children.
- `update(idx, l, r, ql, qr, base, L)`
  - Updates the range `[ql, qr]` with the arithmetic progression formula.
- `query(idx, l, r, ql, qr)`
  - Returns the sum for the range `[ql, qr]`, applying pending lazy updates as needed.

### Arithmetic progression helper

- `getAPSum(start, len)` calculates the sum of the arithmetic progression:
  `start + (start + 1) + ... + (start + len - 1)`.
- `modMul(a, b)` performs multiplication modulo `10^9 + 7`.

## Input and output

- Input:
  - `n` — number of array elements
  - `A[0..n-1]` — initial array
  - `q` — number of queries
  - `q` queries of the form `t l r`
- Output:
  - One integer: the sum of all type `2` query results modulo `10^9 + 7`

## Notes

- Indexing in the code is `0`-based for the stored array.
- The lazy update uses the initial query index `l` to recompute the correct progression start for every segment.
- `query(1, 0, n-1, l, l)` is used to read the current `A[l]` value before applying a type `1` update.

## Complexity

- Build: `O(n)`
- Each update: `O(log n)` average with lazy propagation
- Each query: `O(log n)`

## Example

Input:
```
7
1 4 5 1 6 7 8
5
1 1 6
1 1 5
2 5 5
2 3 4
2 3 3
```

Output:
```
60
```
