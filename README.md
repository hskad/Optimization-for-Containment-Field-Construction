# Optimization for Containment Field Construction - KRITI'25
> 🥉 **Bronze Medal Winner!**
>
> This project was awarded the **Bronze Medal** in the KRITI'25 Optimization challenge, a testament to its robust and efficient heuristic-based approach.

This repository contains the **Bronze Medal-winning solution** developed by **Dihing Hostel** for the **Optimization** problem statement of **KRITI'25**, the Inter-Hostel technical tournament of IIT Guwahati. The project focuses on solving a complex computational geometry problem under strict performance constraints, employing a multi-heuristic approach to maximize a given objective function.

## Table of Contents
- [1. Project Overview](#1-project-overview)
- [2. The Optimization Problem](#2-the-optimization-problem)
  - [Objective](#objective)
  - [Constraints](#constraints)
  - [Input & Output Format](#input--output-format)
- [3. Our Approach: A Heuristic-Driven Strategy](#3-our-approach-a-heuristic-driven-strategy)
  - [Why Heuristics?](#why-heuristics)
  - [Experimented (and Rejected) Approaches](#experimented-and-rejected-approaches)
  - [The Final Multi-Heuristic Method](#the-final-multi-heuristic-method)
- [4. The Four Core Heuristics](#4-the-four-core-heuristics)
  - [`STRIP_X()`](#strip_x)
  - [`STRIP_Y()`](#strip_y)
  - [`BEST_165()`](#best_165)
  - [`WORST_165()`](#worst_165)
- [5. Implementation Details](#5-implementation-details)
  - [Technology Stack](#technology-stack)
  - [How to Run](#how-to-run)
- [6. Results & Performance](#6-results--performance)
- [7. Challenges Faced](#7-challenges-faced)
- [8. Future Scope](#8-future-scope)
- [9. Competition Context](#9-competition-context)

## 1. Project Overview
The challenge is to construct a containment field (a polygon) in a 2D space populated with valuable **Stellar Crystals** (positive points) and hazardous **Void Mines** (negative points). The goal is to design a polygon that maximizes the net value of the enclosed points. This project involves computational geometry, algorithmic design, and strategic optimization to find a near-optimal solution for large datasets within a tight time limit.

## 2. The Optimization Problem

### Objective
Your space empire must construct an energy containment field to capture Stellar Crystals while avoiding Void Mines. The task is to define a polygon that maximizes the net value `V`, defined as:

$V = \sum_{i \in \text{Stellar Crystals}} c_i - \sum_{j \in \text{Void Mines}} m_j$

where `c_i` is the value of a crystal and `m_j` is the penalty of a mine inside the polygon.

### Constraints
*   **Total Points:** The combined number of Stellar Crystals and Void Mines is 10,000.
*   **Vertices Limit:** The polygon must have no more than **1000 vertices**.
*   **Polygon Type:** The polygon must be **rectilinear**, meaning all its edges are parallel to the x-axis or y-axis.
*   **Simple Polygon:** The polygon must **not self-intersect**.
*   **Coordinate Space:** Vertices must have integer coordinates `(x, y)` where `0 ≤ x, y ≤ 10,000`.
*   **Runtime Limit:** The code must process 20 test cases within a **10-minute** maximum runtime.

### Input & Output Format
*   **Input:** A list of `N` Stellar Crystals `(x_i, y_i, c_i)` and `M` Void Mines `(x_j, y_j, m_j)`.
*   **Output:** The solution must provide:
    1.  The calculated net value (Cost).
    2.  The number of vertices (V) and edges (E).
    3.  A list of all E edges of the polygon.

## 3. Our Approach: A Heuristic-Driven Strategy

### Why Heuristics?
Given the large input size (10,000 points) and the strict 10-minute time limit for 20 test cases, an exhaustive search for the truly optimal polygon is computationally infeasible. The search space is astronomically large. Therefore, we adopted a **greedy, heuristic-based strategy** to find high-quality solutions quickly.

### Experimented (and Rejected) Approaches
We initially considered several classical approaches but discarded them due to their unsuitability for this problem's scale and constraints:
*   **Brute Force Search:** Exponential complexity; impossible to check all valid polygons.
*   **Dynamic Programming:** Would require overly complex state definitions and prohibitive memory usage.
*   **Convex Hull:** Too simplistic. A convex polygon would likely enclose many high-penalty mines, drastically reducing the score.
*   **Clustering Algorithms:** Finding optimal clusters to enclose is itself an NP-hard problem, making it too slow.

### The Final Multi-Heuristic Method
Our final strategy acknowledges that no single greedy approach is perfect for every data distribution. We therefore developed **four distinct heuristic algorithms**. For each test case, we run all four heuristics and select the one that produces the highest net value. This approach provides robustness and adapts better to varied point distributions.

## 4. The Four Core Heuristics

#### `STRIP_X()`
This heuristic divides the 2D space into vertical strips. It calculates a cumulative score for each strip, sorts them by value, and then constructs a polygon that greedily includes the most valuable vertical regions. The polygon is formed using horizontal edges to connect these high-value strips.

#### `STRIP_Y()`
Analogous to `STRIP_X()`, this method divides the space into horizontal strips. It identifies the strips with the highest net value and builds a polygon around them using vertical boundary edges, ensuring an efficient enclosure of horizontally-aligned value.

#### `BEST_165()`
This is a point-centric greedy approach. It identifies the **top 165 highest-scoring Stellar Crystals** and constructs a compact, rectilinear polygon around them. This method excels when high-value crystals are clustered together. The number 165 was determined through experimentation to balance capturing value and keeping the vertex count low.

#### `WORST_165()`
This heuristic works by exclusion. It identifies the **165 most detrimental Void Mines** (those with the highest penalties). It then constructs a polygon that artfully avoids these mines while trying to enclose as many of the remaining positive-value crystals as possible. This is effective when high-penalty mines act as clear "no-go" zones.

## 5. Implementation Details

### Technology Stack
*   **Language:** C++ (for performance-critical computations)
*   **Compiler:** G++ with C++17 standard and O2/O3 optimizations.

### How to Run
1.  **Compile the code:**
    ```bash
    g++ -std=c++17 -O2 main.cpp -o solver
    ```
2.  **Run the solver:**
    The program is designed to read from standard input and write to standard output.
    ```bash
    ./solver < input/testcase_01.txt > output/output_01.txt
    ```

## 6. Results & Performance
By running all four heuristics on each test case and selecting the best outcome, our solution was able to effectively balance score maximization with computational efficiency. Across the test suite, we achieved an **average score of 58.25%** of the estimated maximum possible score, demonstrating the robustness of our multi-pronged approach.

## 7. Challenges Faced
1.  **Handling Large Input Size:** Processing 10,000 points efficiently required optimized data structures and sorting algorithms to avoid bottlenecks.
2.  **Balancing Score vs. Constraints:** The primary challenge was enclosing high-value regions without exceeding the 1000-vertex limit. Our multi-heuristic approach provided the flexibility to find a suitable polygon under this constraint.
3.  **Strict Time Constraints:** Completing 20 test cases in 10 minutes forced the abandonment of exact algorithms in favor of fast, effective greedy strategies.

## 8. Future Scope
While our solution proved effective, there are several avenues for future improvement:
*   **Implementing Machine Learning:** Train a classifier to predict which of the four heuristics will perform best for a given test case based on input data features (e.g., point density, value distribution), saving runtime by avoiding redundant computations.
*   **Enhancing the Optimization Strategy:** Explore more advanced metaheuristics like **Simulated Annealing** or **Genetic Algorithms** to refine the initial polygons generated by our greedy methods.
*   **Handling Larger & More Complex Datasets:** Optimize the code further to scale to even larger datasets, potentially for real-world applications like geospatial resource planning.

## 9. Competition Context
- **Event:** KRITI'25
- **Organizer:** Techboard, IIT Guwahati
- **Team:** Hostel 76
- **Achievement:** 🥉 **Bronze Medal**
