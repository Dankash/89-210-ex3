#ifndef ASS1_NEIGHBORS_H
#define ASS1_NEIGHBORS_H

#include "Location.h"
#include <iostream>
#include <list>
#include "Grid.h"
using namespace std;
/**
 * represents the locations adjacent to the
 * current location.
 */
class Neighbors {
public:
    /**
 * makes the locations' parent point to another location
 * that way all the paths will  lead to the source location.
 * @param grid - object which contains location 2d array,
 * obstacles, rows and columns.
 * @param current - point to the current locations in the grid.
 * @param neighbors - list which will contain a list with
 * the location's neighbors.
 */
    static void neighborsList(Grid &grid, Location current, list<Location *> &neighbors);
};

#endif //ASS1_NEIGHBORS_H
