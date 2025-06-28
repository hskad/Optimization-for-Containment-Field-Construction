#pragma once
#include "Strategies.h"
#include <memory>

class Solver {
private:
    ProblemContext context;
    std::vector<std::unique_ptr<OptimizationStrategy>> strategies;

public:
    Solver(const std::vector<Node>& crystals, const std::vector<Node>& mines)
        : context(crystals, mines) {
        // Register all strategies to be tested
        strategies.push_back(std::make_unique<StripStrategy>(Axis::X));
        strategies.push_back(std::make_unique<StripStrategy>(Axis::Y));
        strategies.push_back(std::make_unique<BestNPointsStrategy>());
        strategies.push_back(std::make_unique<WorstNPointsStrategy>());
    }

    Polygon run() {
        Polygon best_polygon;
        
        std::cout << "Starting solver..." << std::endl;

        for (const auto& strategy : strategies) {
            std::cout << "Running strategy: " << strategy->getName() << "..." << std::endl;
            Polygon current_polygon = strategy->solve(context);

            if (current_polygon.score > best_polygon.score) {
                std::cout << "  -> New best score found: " << current_polygon.score << std::endl;
                best_polygon = current_polygon;
            }
        }

        std::cout << "Solver finished. Best score: " << best_polygon.score << std::endl;
        return best_polygon;
    }
};