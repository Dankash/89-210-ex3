
#ifndef ASS1_TAXICENTER_H
#define ASS1_TAXICENTER_H

#include <iostream>
#include <list>
#include "Listener.h"
#include "Driver.h"
#include <iterator>

using namespace std;
/**
 * taxi center class.
 */
class TaxiCenter: public Listener {

private:
    list<Driver*> *employees;
    list<Cab*> *cabs;

public:
/**
 *
 * @param employees - drivers who works in the taxi center.
 * @param cabs - the cabs of the taxi center.
 * @return taxi center object.
 */

    TaxiCenter(list<Driver *> *employees, list<Cab *> *cabs);

    /**
 *
 * @return drivers of the taxi center.
 */
    list<Driver *> *getEmployees() const;

    /**
 *
 * @param employees - set drivers.
 */
    void setEmployees(list<Driver *> *employees);

    /**
 *
 * @return cabs of the center.
 */
    list<Cab *> *getCabs() const;

    /**
 *
 * @param cabs - set cabs of the center.
 */
    void setCabs(list<Cab *> *cabs);

/**
 * a call has occured and a cab needs to pick up the passenger.
 */
    void Event();
/**
 * assign cab for each driver in the employees list
 */
    void assignCabToDriver();
};


#endif //ASS1_TAXICENTER_H
