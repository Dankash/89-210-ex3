#include "Cab.h"
#include "LuxuryCab.h"
#include "StandardCab.h"

Cab::Cab(int id, int type, char brand, char color) : id(id),
          type(type), brand(brand),color(color),location(Location(Point(0,0), NULL)), kilometer(0),
            trip(NULL) {}

Cab::Cab() {

}

int Cab::getId() const {
    return id;
}

void Cab::setId(int id) {
    Cab::id = id;
}

int Cab::getKilometer() const {
    return kilometer;
}

void Cab::setKilometer(int kilometer) {
    Cab::kilometer = kilometer;
}

double Cab::getFee() const {
    return fee;
}

void Cab::setFee(double fee) {
    Cab::fee = fee;
}

const Location &Cab::getLocation() const {
    return location;
}

void Cab::setLocation(const Location &location) {
    Cab::location = location;
}

char Cab::getBrand() const {
    return brand;
}

void Cab::setBrand(char brand) {
    Cab::brand = brand;
}

char Cab::getColor() const {
    return color;
}

void Cab::setColor(char color) {
    Cab::color = color;
}

Trip *Cab::getTrip() const {
    return trip;
}

void Cab::setTrip(Trip *trip) {
    Cab::trip = trip;
}

int Cab::getType() const {
    return type;
}

void Cab::setType(int type) {
    Cab::type = type;
}
const stack<Point> &Cab::getPath() const {
    return path;
}

void Cab::setPath(const stack<Point> &path) {
    Cab::path = path;
}

}




