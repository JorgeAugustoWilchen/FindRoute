#include "findroute.h"


FindRoute::FindRoute()
{

}


FindRoute::~FindRoute() 
{

}


float FindRoute::heuristic(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

std::vector<Node> FindRoute::getNeighbors(const Node& node, const std::vector<std::vector<int>>& grid) {
    std::vector<Node> neighbors;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (const auto& dir : directions) {
        int newX = node.x + dir[0];
        int newY = node.y + dir[1];
        if (newX >= 0 && newY >= 0 && newX < grid.size() && newY < grid[0].size() && grid[newX][newY] == 1) {
            neighbors.emplace_back(newX, newY);
        }
    }
    
    return neighbors;
}

std::vector<Node> FindRoute::reconstructPath(Node* endNode) {
    std::vector<Node> path;
    Node* current = endNode;
    
    while (current != nullptr) {
        path.push_back(*current);
        current = current->parent;
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node> FindRoute::aStar(const std::vector<std::vector<int>>& grid, Node start, Node goal) {
    std::priority_queue<Node> openSet;
    std::unordered_set<Node, NodeHasher> closedSet;

    start.h = heuristic(start.x, start.y, goal.x, goal.y);
    openSet.push(start);

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current == goal) {
            return reconstructPath(&current);
        }

        closedSet.insert(current);

        for (auto& neighbor : getNeighbors(current, grid)) {
            if (closedSet.find(neighbor) != closedSet.end()) {
                continue;
            }

            float tentative_g = current.g + 1; // Assuming cost of 1 for each move
            bool inOpenSet = false;

            if (tentative_g < neighbor.g || !inOpenSet) {
                neighbor.g = tentative_g;
                neighbor.h = heuristic(neighbor.x, neighbor.y, goal.x, goal.y);
                neighbor.parent = new Node(current);

                openSet.push(neighbor);
            }
        }
    }

    return {}; // Return empty path if no path found
}

std::vector<Node> FindRoute::coveragePathPlanning(const std::vector<std::vector<int>>& grid) {
    std::vector<Node> allOnes;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                allOnes.emplace_back(i, j);
            }
        }
    }

    std::vector<Node> fullPath;
    Node start = allOnes[0];
    allOnes.erase(allOnes.begin());
    fullPath.push_back(start);

    while (!allOnes.empty()) {
        float minDistance = std::numeric_limits<float>::max();
        Node nextGoal(0, 0);
        std::vector<Node> bestPath;

        for (auto& goal : allOnes) {
            auto path = aStar(grid, start, goal);
            if (!path.empty() && path.back().getF() < minDistance) {
                minDistance = path.back().getF();
                nextGoal = goal;
                bestPath = path;
            }
        }

        if (bestPath.empty()) {
            break; // Se não encontrar um caminho válido, interrompe
        }

        // Adiciona o caminho encontrado ao caminho total, evitando duplicatas
        for (const auto& node : bestPath) {
            if (fullPath.empty() || fullPath.back() != node) {
                fullPath.push_back(node);
            }
        }

        start = nextGoal;
        allOnes.erase(std::remove(allOnes.begin(), allOnes.end(), nextGoal), allOnes.end());
    }

    return fullPath;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1}
    };

    FindRoute fr;

    std::vector<Node> path = fr.coveragePathPlanning(grid);

    std::cout << "Path: ";
    for (const auto& node : path) {
        std::cout << "(" << node.x << "," << node.y << ") ";
    }

    return 0;
}
