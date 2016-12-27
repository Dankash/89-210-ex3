
#ifndef ASS1_CON_H
#define ASS1_CON_H
#include "Grid.h"
#include "Location.h"
/**
 * connect the locations in the grid
 * that way each location will point
 * to his parent.
 */
class ConnectGrid {
public:
    /**
 * connecct the locations of the grid to each other.
 * @param grid - reference of the grid.
 * @param root - pointer which will be used to point to the locations
 * @param row - number of rows.
 * @param col - number of columns.
 */
    static void connect(Grid &grid, Location* root, int row, int col);
};


#endif //ASS1_CON_H
