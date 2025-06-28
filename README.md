# Optimization for Containment Field Construction - KRITI'25

> 🥉 **Bronze Medal Winner!**
>
> This project was awarded the **Bronze Medal** in the KRITI'25 Optimization challenge, a testament to its robust and efficient heuristic-based approach.

This repository contains the **Bronze Medal-winning solution** developed by **Dihing Hostel** for the **Optimization** problem statement of **KRITI'25**, the inter-hostel technical tournament of IIT Guwahati, conducted by TechBoard IIT Guwahati.

## Table of Contents
- [1. Project Overview](#1-project-overview)
- [2. The Optimization Problem](#2-the-optimization-problem)
- [3. Our Approach: A Multi-Heuristic OOP Design](#3-our-approach-a-multi-heuristic-oop-design)
  - [The Strategy Design Pattern](#the-strategy-design-pattern)
- [4. Code Structure](#4-code-structure)
- [5. The Four Core Heuristics](#5-the-four-core-heuristics)
  - [`StripStrategy`](#stripstrategy)
  - [`BestNPointsStrategy`](#bestnpointsstrategy)
  - [`WorstNPointsStrategy`](#worstnpointsstrategy)
- [6. Implementation Details](#6-implementation-details)
  - [Technology Stack](#technology-stack)
  - [How to Compile and Run](#how-to-compile-and-run)
- [7. Results & Performance](#7-results--performance)
- [8. Challenges Faced](#8-challenges-faced)
- [9. Future Scope](#9-future-scope)
- [10. Competition Context](#10-competition-context)

## 1. Project Overview
The challenge is to construct a rectilinear polygon in a 2D space to maximize the net value of enclosed "Stellar Crystals" (positive points) while avoiding "Void Mines" (negative points). Given the massive scale of the problem space, this project implements a powerful multi-heuristic approach, where several distinct algorithms are run in parallel, and the best result is chosen.

## 2. The Optimization Problem
The goal is to find a simple, rectilinear polygon with at most 1000 vertices that maximizes the net score `V`:

$V = \sum_{i \in \text{Crystals}} c_i - \sum_{j \in \text{Mines}} m_j$

The problem involves 10,000 total points within a `10000x10000` integer coordinate space and a strict 10-minute runtime limit for 20 test cases.

## 3. Our Approach: A Multi-Heuristic OOP Design
A single greedy algorithm is unlikely to perform well on all possible data distributions. Our solution, therefore, runs **four different heuristic strategies** for each test case and selects the one that yields the highest score. This provides robustness and adaptability.

The refactored code is built around a clean, object-oriented design to manage this complexity effectively.

### The Strategy Design Pattern
At the core of our design is the **Strategy Pattern**. We define a common abstract interface, `OptimizationStrategy`, which dictates that every heuristic must have a `solve()` method. Each of our four heuristics is then implemented as a concrete class that inherits from this interface.

This design offers several key advantages:
- **Encapsulation:** Each strategy's logic is self-contained.
- **Extensibility:** New heuristics can be added easily by creating a new class, without modifying the existing solver logic.
- **Readability:** The main solver code is clean and simply iterates through a list of strategies, making the high-level logic easy to follow.

## 4. Code Structure
The code is organized into several headers for clear separation of concerns:

-   **`Constants.h`**: Centralizes all "magic numbers" (e.g., `BEST_N_POINTS = 165`) into named constants for clarity and easy tuning.
-   **`Geometry.h`**: Defines fundamental data structures like `Point`, `Edge`, and `Polygon`. This avoids complex `std::pair` nesting and improves type safety.
-   **`Strategies.h`**: The heart of the object-oriented design.
    -   `ProblemContext`: A class that holds all the shared data for a problem instance (point lists, coordinate maps), eliminating the need for global variables.
    -   `OptimizationStrategy`: The abstract base class for our Strategy Pattern.
    -   `StripStrategy`, `BestNPointsStrategy`, `WorstNPointsStrategy`: Concrete implementations of the different heuristics.
-   **`Solver.h`**: Contains the `Solver` class, which orchestrates the entire process. It initializes all strategies, runs them against the problem context, and identifies the best-performing solution.
-   **`main.cpp`**: The entry point of the program. It is responsible only for handling file I/O, parsing the input, creating the `Solver`, and printing the final result.

## 5. The Four Core Heuristics

Our solution's strength comes from these four distinct, complementary strategies.

### `StripStrategy`
This class implements the logic for both vertical and horizontal strip-based analysis, configured via an `Axis` enum (`X` or `Y`). It divides the 2D space into parallel strips, calculates a score for each, and constructs a polygon that greedily encloses the most valuable strips. This approach is highly effective when valuable points are aligned along one axis.

### `BestNPointsStrategy`
This is a point-centric greedy approach, implemented in the `BestNPointsStrategy` class. It identifies the **top 165 highest-value Stellar Crystals** and constructs a compact, rectilinear polygon around them. This method excels when high-value crystals are densely clustered.

### `WorstNPointsStrategy`
Implemented in the `WorstNPointsStrategy` class, this heuristic works by exclusion. It starts with a polygon enclosing the entire space and then carves out "holes" to exclude the **165 most detrimental Void Mines**. This is effective when high-penalty mines act as clear "no-go" zones that can be easily isolated.

## 6. Implementation Details

### Technology Stack
- **Language:** C++17
- **Core Concepts:** Object-Oriented Programming, Strategy Design Pattern.
- **Compiler:** G++ with `-O2` or `-O3` optimization flags.

### How to Compile and Run
1.  **Organize Files:** Place all `.h` and `.cpp` files in the same directory.
2.  **Compile the Code:**
    ```bash
    g++ -std=c++17 -O2 main.cpp -o solver
    ```
3.  **Prepare Input/Output:** The input and output file paths are hardcoded in `main.cpp`. Modify these lines to match your test case files:
    ```cpp
    // In main.cpp
    setup_io("input/input09.txt", "output/output09.txt");
    ```
4.  **Run the Solver:**
    ```bash
    ./solver
    ```

## 7. Results & Performance
By running all four heuristics and selecting the best outcome, our solution achieved an **average score of 58.25%** of the estimated maximum, a result strong enough to secure the Bronze Medal.

## 8. Challenges Faced
1.  **Handling Large Input Size:** Required the use of efficient data structures (`std::map`, `std::set`) and algorithms.
2.  **Balancing Score vs. Constraints:** The primary challenge was enclosing high-value regions without exceeding the 1000-vertex limit.
3.  **Strict Time Constraints:** The OOP structure, combined with efficient C++, allowed our greedy strategies to execute well within the time limit.

## 9. Future Scope
- **ML-Powered Heuristic Selection:** Train a model to predict the best heuristic for a given input, skipping the execution of less promising ones to save time.
- **Advanced Metaheuristics:** Use the output of our greedy strategies as a starting point for refinement algorithms like Simulated Annealing or Genetic Algorithms.
- **Code Refinement:** The logic for `BestNPointsStrategy` and `WorstNPointsStrategy` in the refactored code uses simple bounding boxes. The original, more complex polygon-winding logic could be integrated into these classes for potentially higher scores.

## 10. Competition Context
- **Event:** KRITI'25
- **Organizer:** TechBoard, IIT Guwahati
- **Team:** Dihing Hostel
- **Achievement:** 🥉 **Bronze Medal**
