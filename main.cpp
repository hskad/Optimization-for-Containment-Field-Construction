#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Solver.h"

// Helper to handle file I/O
void setup_io(const std::string& input_file, const std::string& output_file) {
    static std::ifstream in(input_file);
    if (!in.is_open()) {
        std::cerr << "Error opening input file: " << input_file << std::endl;
        exit(1);
    }
    std::cin.rdbuf(in.rdbuf());

    static std::ofstream out(output_file);
    if (!out.is_open()) {
        std::cerr << "Error opening output file: " << output_file << std::endl;
        exit(1);
    }
    std::cout.rdbuf(out.rdbuf());
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Change file names as needed
    setup_io("input/input09.txt", "output/output09.txt");

    // 1. Read Input
    int n, m;
    std::vector<Node> crystals, mines;

    std::cin >> n;
    crystals.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> crystals[i].x >> crystals[i].y >> crystals[i].val;
    }

    std::cin >> m;
    mines.resize(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> mines[i].x >> mines[i].y >> mines[i].val;
        mines[i].val *= -1; // Standardize penalties to negative values
    }

    // 2. Create and run the solver
    Solver solver(crystals, mines);
    Polygon best_solution = solver.run();

    // 3. Print the output in the required format
    std::cout << best_solution.score << std::endl;
    std::cout << best_solution.getVertexCount() << ", " << best_solution.edges.size() << std::endl;
    for (const auto& edge : best_solution.edges) {
        std::cout << "(" << edge.p1.x << ", " << edge.p1.y << "), ("
                  << edge.p2.x << ", " << edge.p2.y << ")" << std::endl;
    }

    return 0;
}