#include <iostream>
#include "Grid.h"
using namespace std;

Grid::Grid(Location **locations, list<Point> obstacles, int row, int col) {
    setLocations(locations);
    setObstacles(obstacles);
    setRow(row);
    setCol(col);


    for(int i = 0; i < row; ++i) {
        for (int j = 0; j < col ; ++j) {

            std::list<Location*> neighbors;
            Location *neighbor;

            if (Grid::isInGrid(i - 1, j)) {
                neighbor = &locations[i - 1][j];
                if (neighbor->getDistance() == 10000) {
                    neighbors.push_back(neighbor);
                }
            }

            if (Grid::isInGrid(i, j + 1)) {
                neighbor = &locations[i][j + 1];
                if (neighbor->getDistance() == 10000)
                    neighbors.push_back(neighbor);
            }

            if (Grid::isInGrid(i + 1, j)) {
                neighbor = &locations[i + 1][j];
                if (neighbor->getDistance() == 10000)
                    neighbors.push_back(neighbor);
            }

            if (Grid::isInGrid(i, j - 1)) {
                neighbor = &locations[i][j - 1];
                if (neighbor->getDistance() == 10000)
                    neighbors.push_back(neighbor);
            }

            locations[i][j].setNeighbors(neighbors);

        }
    }

}

Grid::~Grid() {
    delete []locations;
}

Location **Grid::getLocations() const {
    return locations;
}

void Grid::setLocations(Location **locations) {
    Grid::locations = locations;
}

const list <Point> &Grid::getObstacles() const {
    return obstacles;
}

void Grid::setObstacles(const list <Point> &obstacles) {
    Grid::obstacles = obstacles;
}

void Grid::setRow(int row) {
    Grid::row = row;
}

void Grid::setCol(int col) {
    Grid::col = col;
}

int Grid::getRow() {
    return row;
}

int Grid::getCol() {
    return col;
}

bool Grid::isInGrid(int i, int j) {
    return (i >= 0) && (i < row) && (j >= 0) && (j < col);
}

void Grid::resetGrid() {
    list<Point>::iterator it;
    list<Point>::iterator itEnd;
    it = obstacles.begin();
    itEnd = obstacles.begin();
    advance(itEnd, obstacles.size() - 1);
    Point point;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            it = obstacles.begin();
            for (int k = 0; k < obstacles.size(); ++k) {
                point = *(it);
                if(point == locations[i][j].getPoint())
                    locations[i][j].setDistance(-1);
                else
                    if(locations[i][j].getDistance() != -1)
                        locations[i][j].setDistance(10000);
                advance(it, 1);
            }

        }
    }

}


