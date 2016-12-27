#ifndef ASS1_LOCATION_H
#define ASS1_LOCATION_H

#include "Point.h"
/**
 * represents the Location inside the grid,
 * includes point, distance from source and pointer to
 * his parent.
 */
class Location {
private:
    Point point;
    int distance;
    Location* parent;
public:
    Location();
    /**
 * set the location's params.
 * @param point - the point of the location.
 * @param distance - the distance from thee source point.
 * @param location - the parent of the  location.
 * @return
 */
    Location(const Point &point, Location *parent);
    /**
 * destructor
 */
    virtual ~Location();
    /**
 * @return location's point.
 */
    const Point &getPoint() const;
    /**
 * set new point.
 * @param point to be set.
 */
    void setPoint(const Point &point);
    /**
     * get Distance
     * @return Distance.
     */
    int getDistance() const;
    /**
 * set new distance.
 * @param distance to be  set.
 */
    void setDistance(int distance);
    /**
 * @return parent's location.
 */
    Location *getParent() const;
    /**
 * @param parent of the location.
 */
    void setParent(Location *parent);
    /**
 * @param l1 - location which will be compared with the current location.
 * @return true if equals, else false.
 */
    bool operator==(const Location &l1) const;
};


#endif //ASS1_LOCATION_H
