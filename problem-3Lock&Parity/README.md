# Lock & Parity Problem — Solution Walkthrough

<p align="center">
<img src="./ques.png" width="600">
</p>

This repository contains solutions to the **Lock & Parity assignment problem** implemented in C++.
The goal is to determine a valid set of key-lock assignments that minimizes the total cost while satisfying a parity constraint.

The README explains the **problem understanding and the evolution of solutions**, starting from a naive brute force approach and progressing toward an optimized solution.

---

# Table of Contents

1. Problem Summary
2. Constraints
3. Assignment Rules
4. Parity Constraint
5. Approach 1 — Brute Force
6. Approach 2 — Backtracking
7. Approach 3 — Observing Parity Properties
8. Approach 4 — Greedy Insight
9. Approach 5 — Optimized Solution
10. Complexity Analysis
11. Repository Structure

---

# Problem Summary

You are given **N locks arranged in a row (1-indexed)**.

Each lock `i` has a value:

```
L[i]
```

Each lock also has **a key underneath it**.

A key from position `j` can unlock lock `i` if the following conditions are satisfied:

```
j < i
L[j] ≠ L[i]
```

The **cost of assigning key j to lock i** is defined as:

```
|L[j] − L[i]|
```

Your task is to select a valid set of assignments such that the **total cost is minimized**.

---

# Constraints

```
1 ≤ N ≤ 200
1 ≤ L[i] ≤ 100000
```

Additional restrictions:

* Each key can be used **at most once**
* Each lock can be assigned **at most once**
* At least **one assignment must be selected**

---

# Assignment Rules

A valid assignment must satisfy:

1. Direction constraint

```
j < i
```

A key can only unlock locks positioned **to its right**.

2. Value constraint

```
L[j] ≠ L[i]
```

Assignments between locks with identical values are not allowed.

3. Cost definition

```
cost = |L[j] − L[i]|
```

---

# Parity Constraint

After selecting all assignments, the following condition must hold:

```
number_of_even_cost_edges ≥ number_of_odd_cost_edges
```

Definitions:

```
even edge → cost is even
odd edge  → cost is odd
```

Examples of valid selections:

| Even | Odd | Valid |
| ---- | --- | ----- |
| 1    | 0   | Yes   |
| 1    | 1   | Yes   |
| 2    | 1   | Yes   |
| 0    | 1   | No    |
| 0    | 2   | No    |

If no valid assignment set exists, the output should be:

```
-1
```

---

# Approach 1 — Brute Force (Conceptual)

Idea:

1. Generate every possible valid assignment `(j, i)`
2. Enumerate **all subsets** of assignments
3. For each subset check:

   * keys are not reused
   * locks are not reused
   * parity rule is satisfied
4. Track the minimum cost.

Although this guarantees correctness, it is computationally infeasible.

Total possible subsets:

```
2^E
```

Where `E` is the number of edges (assignments).

Worst-case `E` can reach nearly `N²`.

### Complexity

```
O(2^E)
```

This approach becomes impossible even for small values of `N`.

Implementation available in:

```
brute.cpp
```

---

# Approach 2 — Backtracking

A refinement of brute force uses recursion and pruning.

During recursion we maintain:

```
used_keys[]
used_locks[]
even_count
odd_count
current_cost
```

Steps:

1. Select an unused assignment
2. Mark key and lock as used
3. Update parity counts
4. Recurse to explore further assignments
5. Backtrack

Although pruning removes some invalid states early, the worst-case complexity remains exponential.

### Complexity

```
O(2^E)
```

Still not suitable for the given constraints.

---

# Approach 3 — Observing the Parity Rule

The main constraint is:

```
even_edges ≥ odd_edges
```

Important observations:

* Odd edges alone cannot form a valid solution
* Even edges alone always satisfy the constraint
* Odd edges must be balanced by even edges

Valid patterns include:

```
1 even
1 even + 1 odd
2 even + 1 odd
2 even + 2 odd
```

This insight significantly reduces the search space.

---

# Approach 4 — Greedy Insight

A **single even edge** already satisfies the constraint:

```
even = 1
odd  = 0
```

Therefore, the smallest valid solution could simply be the **minimum even-cost edge**.

However, combinations such as:

```
1 even + 1 odd
```

might sometimes produce a smaller total cost depending on edge values.

This motivates evaluating small balanced combinations.

---

# Approach 5 — Optimized Solution

Steps:

### 1. Generate all valid assignments

For all pairs:

```
j < i
L[j] ≠ L[i]
cost = |L[j] − L[i]|
```

### 2. Separate costs by parity

```
even_costs
odd_costs
```

### 3. Sort both lists

```
sort(even_costs)
sort(odd_costs)
```

### 4. Evaluate valid combinations

Possible candidate solutions:

```
1 even
1 even + 1 odd
2 even + 2 odd
3 even + 3 odd
...
```

For each candidate combination ensure:

```
even ≥ odd
```

Compute the minimum achievable cost.

Implementation available in:

```
optimal_sol.cpp
```

---

# Complexity Analysis

Generating edges:

```
O(N²)
```

Sorting edge lists:

```
O(E log E)
```

Where:

```
E ≤ N²
```

With `N ≤ 200`, this solution runs comfortably within limits.

---

# Repository Structure

```
problem-3Lock&Parity/
│
├── brute.cpp
├── optimal_sol.cpp
├── ques.png
└── README.md
```

File descriptions:

```
brute.cpp        : conceptual brute force implementation
optimal_sol.cpp  : optimized implementation used for final solution
ques.png         : problem statement image
README.md        : detailed explanation of approaches
```

---

# Conclusion

The key challenge in this problem lies in balancing **cost minimization** with the **parity constraint**.

Initial brute-force approaches explore all possibilities but are computationally infeasible.
By analyzing the parity property of assignments, we can significantly reduce the search space and derive an efficient solution.

The final algorithm efficiently evaluates feasible combinations of even and odd edges and computes the minimum valid assignment cost.
