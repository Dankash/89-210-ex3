#include "TransportationMap.h"

TransportationMap::TransportationMap(const Grid &grid, const TaxiCenter &taxiCenter) : grid(grid),
                                                                                       taxiCenter(taxiCenter) {}

const Grid &TransportationMap::getGrid() const {
    return grid;
}

void TransportationMap::setGrid(const Grid &grid) {
    TransportationMap::grid = grid;
}

const TaxiCenter &TransportationMap::getTaxiCenter() const {
    return taxiCenter;
}

void TransportationMap::setTaxiCenter(const TaxiCenter &taxiCenter) {
    TransportationMap::taxiCenter = taxiCenter;
}

void TransportationMap::GetPassengerCall() {

}





