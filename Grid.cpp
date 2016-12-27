#include <iostream>
#include "Grid.h"
using namespace std;

Grid::Grid(Location **locations, list<Point> obstacles, int row, int col) {
    setLocations(locations);
    setObstacles(obstacles);
    setRow(row);
    setCol(col);
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
    return (i >= 0) && (i < row) && (j >= 0) && (j <= col);
}
