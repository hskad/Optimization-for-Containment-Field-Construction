#pragma once

namespace Constants {
    // Coordinate space boundaries
    constexpr double COORD_MIN = 0.0;
    constexpr double COORD_MAX = 10000.0;

    // Heuristic parameters
    constexpr int BEST_N_POINTS = 165;
    constexpr int WORST_N_POINTS = 165;
    constexpr int STRIP_MAX_POLYGONS = 250;
    
    // Search parameters for StripStrategy
    constexpr int STRIP_THRESHOLD_START = 0;
    constexpr int STRIP_THRESHOLD_END = -45000;
    constexpr int STRIP_THRESHOLD_STEP = -1000;

    // Small offsets to avoid coordinate collision and define polygon boundaries
    constexpr double EPSILON_1 = 0.1;
    constexpr double EPSILON_2 = 0.2;
    constexpr double EPSILON_3 = 0.3;
    constexpr double EPSILON_5 = 0.5;
}