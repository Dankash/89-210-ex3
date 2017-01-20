#include <iostream>
#include "Location.h"

using namespace std;
/**
 * set the location's params.
 */
Location::Location(): point(0,0) {
    distance = 10000;
    Location::parent = NULL;
}

Location::Location(const Point &point, Location *location) : point(point), parent(location) {
    setPoint(point);
    setDistance(10000);
    setParent(location);
}

Location::~Location() {

}

const Point &Location::getPoint() const {
    return point;
}

void Location::setPoint(const Point &point) {
    Location::point = point;
}
/**
 * @return the distance from the source point.
 */
int Location::getDistance() const {
    return distance;
}

void Location::setDistance(int distance) {
    Location::distance = distance;
}

Location *Location::getParent() const {
    return parent;
}

void Location::setParent(Location *parent) {
    Location::parent = parent;
}

bool Location::operator==(const Location& l1) const {
    return (distance == l1.distance) && (point==l1.point); // should we add locations comparison??
}

const list<Location *> &Location::getNeighbors() const {
    return neighbors;
}

void Location::setNeighbors(const list<Location *> &neighbors) {
    Location::neighbors = neighbors;
}


