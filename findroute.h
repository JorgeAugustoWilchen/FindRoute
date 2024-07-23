#ifndef FINDROUTE_H
#define FINDROUTE_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <limits>

struct Node {
    int x, y;
    float g, h; // g: cost from start to this node, h: heuristic cost to goal
    Node* parent;

    Node(int x, int y, float g = 0, float h = 0, Node* parent = nullptr) 
        : x(x), y(y), g(g), h(h), parent(parent) {}

    float getF() const { return g + h; }
    
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Node& other) const {
        return !(*this == other);
    }

    bool operator<(const Node& other) const {
        return getF() > other.getF(); // Inverted for priority queue
    }
};

struct NodeHasher {
    size_t operator()(const Node& node) const {
        return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1);
    }
};

class FindRoute {
public:
    FindRoute();
    ~FindRoute();

    std::vector<Node> coveragePathPlanning(const std::vector<std::vector<int>>& grid);

private:

    float heuristic(int x1, int y1, int x2, int y2);
    std::vector<Node> getNeighbors(const Node& node, const std::vector<std::vector<int>>& grid);
    std::vector<Node> reconstructPath(Node* endNode);
    std::vector<Node> aStar(const std::vector<std::vector<int>>& grid, Node start, Node goal);
};

#endif // FINDROUTE_H
