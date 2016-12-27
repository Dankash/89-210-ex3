#ifndef ASS1_PASSENGER_H
#define ASS1_PASSENGER_H

#include "Point.h"
#include "Listener.h"
#include "Notifier.h"
#include <iostream>
#include <list>
/**
 * Create Passenger object.
 */
using namespace std;

class Passenger: public Notifier {
private:
    Point sourcePoint;
    Point destinationPoint;
    list<Listener*> listeners;
public:
    /**
 * Constructor.
 * @param sourcePoint
 * @param destinationPoint
 * @param listeners
 * @return
 */
    Passenger(const Point &sourcePoint, const Point &destinationPoint, const list<Listener *> listeners);
/**
 * Satisfaction.
 * @return .
 */

    int Satisfaction();
    /**
 * Notify all the listenres.
 * @param l
 */
    virtual void NotifyCall(list<Listener*> l);
    /**
 * get source point.
 * @return return source point.
 */
    const Point &getSourcePoint() const;
    /**
 * set the source point.
 * @param sourcePoint
 */
    void setSourcePoint(const Point &sourcePoint);
/**
 * get the destination point.
 * @return destintion point.
 */
    const Point &getDestinationPoint() const;
/**
 * set destination point.
 * @param destinationPoint.
 */
    void setDestinationPoint(const Point &destinationPoint);
/**
 * get listeners list.
 * @return listeners.
 */
    const list <Listener*> &getListeners() const;
/**
 * set listeners list.
 * @param listeners.
 */
    void setListeners(const list <Listener*> &listeners);
    /**
 *
 * @param l
 */
    void AddCallListener(Listener *l);
    /**
 *
 * @param l
 */
    void RemoveCallListener(Listener *l);
    /**
 *
 * @return random score of a driver.
 */
    int RandomScore();
};


#endif //ASS1_PASSENGER_H
