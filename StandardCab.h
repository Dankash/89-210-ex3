#ifndef ASS1_STANDARTCAB_H
#define ASS1_STANDARTCAB_H
#include "Cab.h"
/**
 * Create Standard cab object.
 */
class StandardCab: public Cab {
public:
/**
 * Constructor.
 * @param id
 * @param kilometer
 * @param brand
 * @param color
 * @param fee
 * @param location
 * @param trip
 * @return
 */
    StandardCab(int id, int type, char brand, char color);
/**
 * driving car to his destination point
 */
    void Drive();
};


#endif //ASS1_STANDARTCAB_H
