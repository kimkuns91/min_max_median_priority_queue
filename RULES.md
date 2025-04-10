[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/uUoS2HCX)
[![Work in MakeCode](https://classroom.github.com/assets/work-in-make-code-8824cc13a1a3f34ffcd245c82f0ae96fdae6b7d554b6539aec3a03a70825519c.svg)](https://classroom.github.com/online_ide?assignment_repo_id=19108570&assignment_repo_type=AssignmentRepo)
# Min-Max-Median Priority Queue

## Problem Description

In this assignment, you will implement a **Min-Max-Median Priority Queue** in C using efficient data structures such as heaps. Your goal is to ensure that each operation performs efficiently and correctly under a high volume of operations.

---

## Task

**Implement the following operations** for a priority queue storing unique integers:

- `void insert(int element)` — Inserts an element into the queue.
- `int delete_min()` — Removes and returns the minimum element.
- `int delete_max()` — Removes and returns the maximum element.
- `int delete_median()` — Removes and returns the median element.
- `int find_min()` — Prints the minimum element without removing it.
- `int find_max()` — Prints the maximum element without removing it.
- `int find_median()` — Prints the median element without removing it.

**Constraints and Requirements**:
- All elements are guaranteed to be unique.
- If the queue is empty and a delete operation is attempted, it should **do nothing**.
- If the queue is empty and a find operation is attempted, print `NULL`.
- Median is defined as the **smaller** of the two middle elements when the size is even.
- You must use efficient data structures (e.g., **min-heap + max-heap**) for optimal performance.
- **Avoid linear search or sorting for each operation**.

---

## Input Format

- The program reads from a file named `pq.in`.
- The first line contains an integer `N` (1 ≤ N ≤ 500000), the number of operations.
- Each of the following `N` lines contains one operation:
  - Insert: `I <integer>`
  - Delete: `D M` (min), `D X` (max), `D E` (median)
  - Find: `F M` (min), `F X` (max), `F E` (median)

---

## Output Format

- Output must be written to a file named `pq.out`.
- Only **find** operations produce output.
- Each result should be printed on a new line.
- If the queue is empty during a find, print `NULL`.

---

## Example

### Input: `pq.in`
```
8
I 5
I 10
I 20
I 15
D M
F M
F X
F E
```

### Output: `pq.out`
```
10
20
15
```

---

## Submission Guidelines

1. Submit a C file named `pq.c` containing your full implementation.
2. Use ANSI C. Your code must compile using `gcc` on Ubuntu Linux.
3. Do **not** use external libraries or built-in sorting algorithms (e.g., `qsort()` not allowed).
4. Allowed: standard string functions (e.g., `strcmp`, `strcpy`, `strlen`) and file I/O.
5. Include detailed comments explaining your approach and data structure design.
6. Submit the following to your GitHub repository:
   - Your C source code (`pq.c`)
   - An empty file named with your university student ID (e.g., 2024311XXX) to help identify your submission
   - A report (PDF, Korean or English) including:
     - Explanation of your implementation
     - Design choices and algorithm
     - Experimental performance analysis and theoretical comparison

---

## **Evaluation Criteria**  
- **Test Cases:** 4 cases, each worth 2 points (**total: 8 points**, **time limit: 3s**)  
- **Documentation:** 2 points  
- **Total:** 10 points  

Good luck, and happy coding!

---
