
#ifndef ASS1_LUXURYCAB_H
#define ASS1_LUXURYCAB_H


#include "Cab.h"
/**
 * Create luxury cab object.
 */
class LuxuryCab: public Cab {
public:
/**
 * Contructor.
 * @param id
 * @param kilometer
 * @param brand
 * @param color
 * @param fee
 * @param location
 * @param trip
 * @return
 */
    LuxuryCab(int id, int type, char brand, char color);
/**
 * driving car to his destination point
 */
    void Drive();
};


#endif //ASS1_LUXURYCAB_H
