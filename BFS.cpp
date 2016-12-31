#include <stack>
#include <iostream>
#include "BFS.h"

std::stack<Point> BFS::bfs(Grid& grid, Point source, Point destination) {
    Location* destLocation;
    std::stack<Point> path;

    for (int i = 0; i < grid.getRow(); ++i) {
        for (int j = 0; j < grid.getCol(); ++j) {
            if (grid.getLocations()[i][j].getPoint() == destination) {
                destLocation = &grid.getLocations()[i][j];
                break;
            }
        }
    }
    grid.resetGrid();
    while (destLocation != NULL) {
        path.push(destLocation->getPoint());
        destLocation = destLocation->getParent();
    }

    return path;
    /*while (!path.empty()) {
        std::cout<<path.top();
        path.pop();
    }*/
}