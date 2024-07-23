#include "findroute.h"

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0, 0}
    };

    FindRoute fr;

    std::vector<int> path = fr.coveragePathPlanning(grid);

    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); i += 2) {
        std::cout << "(" << path[i] << "," << path[i + 1] << ") ";
    }
    std::cout << std::endl;

    return 0;
}