#ifndef ASS1_TRANSPORTATIONMAP_H
#define ASS1_TRANSPORTATIONMAP_H


#include "Grid.h"
#include "TaxiCenter.h"
/**
 * represents the main flow of the program.
 */
class TransportationMap {
private:
    Grid grid;
    TaxiCenter taxiCenter;

public:
/**
 *
 * @param grid - the grid of the transportation map.
 * @param taxiCenter - the taxi center.
 * @return transportation map object.
 */
    TransportationMap(const Grid &grid, const TaxiCenter &taxiCenter);
/**
 * announce on call from the passenger.
 */
    void GetPassengerCall();
    void BFS(Grid, Location);
    /**
 *
 * @return griid of  the transportation map.
 */
    const Grid &getGrid() const;
    /**
 *
 * @param grid - set new grid.
 */
    void setGrid(const Grid &grid);
    /**
 *
 * @return taxi center of transportation map.
 */
    const TaxiCenter &getTaxiCenter() const;
    /**
 *
 * @param taxiCenter - set taxi center.
 */
    void setTaxiCenter(const TaxiCenter &taxiCenter);
};


#endif //ASS1_TRANSPORTATIONMAP_H
