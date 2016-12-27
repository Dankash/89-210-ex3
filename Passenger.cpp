#include "Passenger.h"


Passenger::Passenger(const Point &sourcePoint, const Point &destinationPoint, const list<Listener *> listeners)
        : sourcePoint(sourcePoint), destinationPoint(destinationPoint), listeners(listeners) {}

void Passenger::NotifyCall(std::list <Listener*> l) {

}

const Point &Passenger::getSourcePoint() const {
    return sourcePoint;
}

void Passenger::setSourcePoint(const Point &sourcePoint) {
    Passenger::sourcePoint = sourcePoint;
}

const Point &Passenger::getDestinationPoint() const {
    return destinationPoint;
}

void Passenger::setDestinationPoint(const Point &destinationPoint) {
    Passenger::destinationPoint = destinationPoint;
}

const list <Listener*> &Passenger::getListeners() const {
    return listeners;
}

void Passenger::setListeners(const list <Listener*> &listeners) {
    Passenger::listeners = listeners;
}
int Passenger::Satisfaction() {
    return 0;
}

void Passenger::AddCallListener(Listener *l) {

}

void Passenger::RemoveCallListener(Listener *l) {

}

int Passenger::RandomScore() {
    return 1;
}













