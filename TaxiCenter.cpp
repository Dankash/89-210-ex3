#include <tgmath.h>
#include "TaxiCenter.h"


TaxiCenter::TaxiCenter(std::list < Driver * > *employees, list < Cab * > *cabs): employees(employees), cabs(cabs) {}

void TaxiCenter::Event() {

}

void TaxiCenter::assignCabToDriver() {
    int i, j;
    list<Cab *>::iterator cabItStart;
    list<Cab *>::iterator cabItEnd;
    cabItStart = cabs->begin();
    cabItEnd = cabs->begin();
    advance(cabItEnd, cabs->size() - 1);
    list<Driver *>::iterator drItStart;
    list<Driver *>::iterator drItEnd;
    drItStart = employees->begin();
    drItEnd = employees->begin();
    advance(drItEnd, employees->size() - 1);
    for (i = 0; i < cabs->size(); i++) {
        for (j = 0; j < employees->size(); j++) {
            Driver *driver = *drItStart;
            Cab *cab = *cabItStart;
            if (cab->getId() == driver->getCabId()) {
                driver->setCab(cab);
            }
            if(drItStart != drItEnd)
                advance(drItStart, 1);
        }
        if(cabItStart != cabItEnd)
            advance(cabItStart, 1);
    }
}

list<Driver *> *TaxiCenter::getEmployees() const {
    return employees;
}

void TaxiCenter::setEmployees(std::list < Driver * > *employees) {
    TaxiCenter::employees = employees;
}

list<Cab *> *TaxiCenter::getCabs() const {
    return cabs;
}

void TaxiCenter::setCabs(std::list < Cab * > *cabs) {
    TaxiCenter::cabs = cabs;
}


