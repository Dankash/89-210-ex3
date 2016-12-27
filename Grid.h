#ifndef ASS1_GRID_H
#define ASS1_GRID_H

#include "Location.h"
#include <list>
using namespace std;
/**
 * Grid represent a net of locations.
 */
class Grid {
private:

    Location** locations;
    std::list<Point> obstacles;
    int row;
    int col;

public:
    /**
 * sets the params of the grid.
 * @param locations - 2d dynamic array of locations.
 * @param obstacles - points which represent obstacles.
 * @param row - number of rows.
 * @param col - number of columns.
 * @return the grid.
 */
    Grid(Location **locations, list <Point> obstacles, int row, int col);
    /**
 * destructor free the locations memory.
 */
    ~Grid();
    /**
 * @return the 2d array of locations.
 */
    Location **getLocations() const;
    /**
 *
 * @param locations to be set in the grid.
 */
    void setLocations(Location **locations);
/**
 * @return the row of the grid.
 */
    int getRow();
    /**
 * @return the col of the grid.
 */
    int getCol();
    /**
 *
 * @param row to be set.
 */
    void setRow(int row);
    /**
 *
 * @param col to be sest.
 */
    void setCol(int col);
    /**
 * @return the obstacles (points) of the grid.
 */
    const list <Point> &getObstacles() const;
    /**
 * @param obstacles to be set in the grid.
 */
    void setObstacles(const list <Point> &obstacles);
    /**
 * @param i - the x axis.
 * @param j - the y axis.
 * @return true if the points are equals, otherwise false.
 */
    bool isInGrid(int i, int j);
};


#endif //ASS1_GRID_H
