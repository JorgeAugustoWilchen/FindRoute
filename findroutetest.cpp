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

    std::pair<int, int> start(0, 0);
    std::pair<int, int> goal(7, 9);
    //std::vector<int> path = fr.coveragePathPlanning(grid);
    //std::vector<int> path = fr.coveragePathPlanning(grid, start, goal);
    std::vector<std::pair<int, int>> path = fr.smallPath(grid, start, goal);

    std::cout << "Path: ";
    for (const auto& p : path) {
        std::cout << "(" << p.first << ", " << p.second << ")";
    }
    std::cout << std::endl;

    return 0;
}