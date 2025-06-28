#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

// A simple 2D point structure. Using double for fractional coordinates.
struct Point {
    double x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Represents a single edge of the polygon.
// Ensures canonical representation (p1 < p2) for easy comparison and set insertion.
struct Edge {
    Point p1, p2;

    Edge(Point a, Point b) {
        if (b < a) std::swap(a, b);
        p1 = a;
        p2 = b;
    }

    bool operator<(const Edge& other) const {
        if (p1 < other.p1) return true;
        if (other.p1 < p1) return false;
        return p2 < other.p2;
    }
};

// Represents a complete solution: a score and the polygon that achieves it.
struct Polygon {
    long long score = -1e18; // Initialize with a very low score
    std::set<Edge> edges;

    size_t getVertexCount() const {
        std::set<Point> vertices;
        for (const auto& edge : edges) {
            vertices.insert(edge.p1);
            vertices.insert(edge.p2);
        }
        return vertices.size();
    }
};

// Basic data structure for crystals and mines
struct Node {
    long long x, y, val;
};