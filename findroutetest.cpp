#include "findroute.h"

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0}
    };

    FindRoute fr;

    std::vector<Node> path = fr.coveragePathPlanning(grid);

    std::cout << "Path: ";
    for (const auto& node : path) {
        std::cout << "(" << node.x << "," << node.y << ") ";
    }

    return 0;
}