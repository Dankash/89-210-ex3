
#ifndef ASS1_CAB_H
#define ASS1_CAB_H

#include <iostream>
#include "Location.h"
#include "Trip.h"

using namespace std;

class Cab {
protected:
    int id;
    int kilometer;
    int type;
    char brand;
    char color;
    double fee;
    Location location;
    Trip* trip;
public:
    /**
     *
     * @param id - id of cab.
     * @param kilometer passed of cab.
     * @param brand of cab.
     * @param color of cab.
     * @param fee of cab.
     * @param location of cab.
     * @param trip of cab.
     * @return cab object.
     */

    Cab(int id, int type, char brand, char color);

    /**
     * represents the drive of the cab.
     */
    virtual void Drive() = 0;
    /**
     *
     * @return id of cab.
     */
    int getId() const;
    /**
     *
     * @param id - set id of cab.
     */
    void setId(int id);
    /**
     *
     * @return passed kilometers  of the cab.
     */
    int getKilometer() const;
    /**
     *
     * @param kilometer - set kilometer of cab.
     */
    void setKilometer(int kilometer);
    /**
     *
     * @return get brand of cab.
     */
    char getBrand() const;
    /**
     *
     * @param brand - set brand  of cab.
     */
    void setBrand(char brand);
    /**
     *
     * @return color of  cab.
     */
    char getColor() const;
    /**
     *
     * @param color - set color of cab.
     */
    void setColor(char color);
    /**
     *
     * @return the fee of the cab.
     */
    double getFee() const;
    /**
     *
     * @param fee - set fee of the cab.
     */
    void setFee(double fee);
    /**
     *
     * @return location of the cab.
     */
    const Location &getLocation() const;
    /**
     *
     * @param location - set location of the cab.
     */
    void setLocation(const Location &location);
    /**
     *
     * @return trip of the cab.
     */
    Trip *getTrip() const;
    /**
     *
     * @param trip - set trip of cab.
     */
    void setTrip(Trip *trip);
    /**
     *
     * @return default object of cab.
     */
    Cab();
    /**
     *
     * @return type of cab.
     */
    int getType() const;
    /**
     *
     * @param type - seet type of cab.
     */
    void setType(int type);


};

#endif //ASS1_CAB_H
