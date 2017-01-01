#ifndef ASS1_TRIP_H
#define ASS1_TRIP_H

#include "Point.h"
/**
 * class which represents the trip.
 */
class Trip {
private:
    int rideId;
    int totalMetersPassed;
    Point startPoint;
    Point endPoint;
    int numberOfPassengers;
    double fare;

    //friend class boost::serialization::access;


public:
    /*template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & rideId;
        ar & totalMetersPassed;
        ar & startPoint;
        ar & endPoint;
        ar & numberOfPassengers;
        ar & fare;
    }*/

    /**
 *
 * @param rideId - the id of the ride.
 * @param totalMetersPassed - passed meters of the trip.
 * @param startPoint - the start point.
 * @param endPoint - the end point.
 * @param numberOfPassengers - number of passengers in the cab.
 * @param fare - fare of the trip.
 * @return trip object.
 */
    Trip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int numberOfPassengers,
         double fare);
    /**
 *
 * @return trip object.
 */
    Trip();
    /**
 *
 * @return id of trip.
 */
    int getRideId() const;
    /**
*
* @param rideId - set new trip id.
*/
    void setRideId(int rideId);
    /**
 *
 * @return total meters of the trip.
 */
    int getTotalMetersPassed() const;

    /**
 *
 * @param totalMetersPassed - total meters of the trip.
 */
    void setTotalMetersPassed(int totalMetersPassed);
/**
 *
 * @return start point.
 */
    const Point &getStartPoint() const;
    /**
 *
 * @param startPoint - set start point.
 */
    void setStartPoint(const Point &startPoint);
    /**
 *
 * @return end point.
 */
    const Point &getEndPoint() const;
    /**
 *
 * @param endPoint - set end point.
 */
    void setEndPoint(const Point &endPoint);
    /**
 *
 * @return number of passengers in the cab.
 */
    int getNumberOfPassengers() const;
    /**
 *
 * @param numberOfPassengers - set number of passengers.
 */
    void setNumberOfPassengers(int numberOfPassengers);
    /**
 *
 * @return fare of trip.
 */
    double getFare() const;
    /**
 *
 * @param fare - set fare.
 */
    void setFare(double fare);
/**
 * setting the x axes of the start point
 * @param x
 */
    void setStartX(int x);
    /**
 * setting the y axes of the start point
 * @param y
 */
    void setStartY(int y);
    /**
 * setting the x axes of the end point
 * @param x
 */
    void setEndX(int x);
    /**
 * setting the y axes of the end point
 * @param y
 */
    void setEndY(int y);

};


#endif //ASS1_TRIP_H
