#include "Trip.h"

Trip::Trip(int rideId, int xStart, int yStart, int  xEnd, int yEnd, int numberOfPassengers,
           double fare) : rideId(rideId), totalMetersPassed(0), startPoint(Point(xStart,yStart)),
                          endPoint(Point(xEnd,yEnd)), numberOfPassengers(numberOfPassengers), fare(fare) {}

Trip::Trip() : startPoint(startPoint),
               endPoint(endPoint) {}

int Trip::getRideId() const {
    return rideId;
}

void Trip::setRideId(int rideId) {
    Trip::rideId = rideId;
}

int Trip::getTotalMetersPassed() const {
    return totalMetersPassed;
}

void Trip::setTotalMetersPassed(int totalMetersPassed) {
    Trip::totalMetersPassed = totalMetersPassed;
}

const Point &Trip::getStartPoint() const {
    return startPoint;
}

void Trip::setStartPoint(const Point &startPoint) {
    Trip::startPoint = startPoint;
}

const Point &Trip::getEndPoint() const {
    return endPoint;
}

void Trip::setEndPoint(const Point &endPoint) {
    Trip::endPoint = endPoint;
}

int Trip::getNumberOfPassengers() const {
    return numberOfPassengers;
}

void Trip::setNumberOfPassengers(int numberOfPassengers) {
    Trip::numberOfPassengers = numberOfPassengers;
}

double Trip::getFare() const {
    return fare;
}

void Trip::setFare(double fare) {
    Trip::fare = fare;
}

void Trip::setStartX(int x) {
    startPoint.SetX(x);
}

void Trip::setStartY(int y) {
    startPoint.SetY(y);
}

void Trip::setEndX(int x) {
    endPoint.SetX(x);
}

void Trip::setEndY(int y) {
    endPoint.SetY(y);
}


int Trip::getTimeOfStart() const {
    return timeOfStart;
}

void Trip::setTimeOfStart(int timeOfStart) {
    Trip::timeOfStart = timeOfStart;
}

