using namespace std;
#include "Neighbors.h"


void Neighbors::neighborsList(Grid& grid, Location current, list<Location*> &neighbors) {

    for(int i = 0; i < grid.getRow(); ++i) {
        for (int j = 0; j < grid.getCol() ; ++j) {
            Location *neighbor;
            if (grid.getLocations()[i][j] == current) {

                if (grid.isInGrid(i - 1, j)) {
                    neighbor = &grid.getLocations()[i - 1][j];
                    if (neighbor->getDistance() == 1000) {
                        neighbors.push_back(neighbor);
                    }
                }

                if (grid.isInGrid(i, j + 1)) {
                    neighbor = &grid.getLocations()[i][j + 1];
                    if (neighbor->getDistance() == 1000)
                        neighbors.push_back(neighbor);
                }

                if (grid.isInGrid(i + 1, j)) {
                    neighbor = &grid.getLocations()[i + 1][j];
                    if (neighbor->getDistance() == 1000)
                        neighbors.push_back(neighbor);
                }

                if (grid.isInGrid(i, j - 1)) {
                    neighbor = &grid.getLocations()[i][j - 1];
                    if (neighbor->getDistance() == 1000)
                        neighbors.push_back(neighbor);
                }

                return;
            }
        }
    }
}