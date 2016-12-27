#include <iostream>
#include "Point.h"

Point::Point(int x_p, int y_p) {
    x = x_p;
    y = y_p;
}

Point::Point() {}

int Point::GetX() const {
    return x;
}

int Point::GetY() const {
    return y;
}

void Point::SetX(int x) {
    Point::x = x;
}

void Point::SetY(int y) {
    Point::y = y;
}

bool Point::operator==(const Point& p1) const {
    return (x == p1.x) && (y == p1.y);
}

bool Point::operator!=(const Point& p1) const {
    return (x != p1.x) || (y != p1.y);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "("<< point.x<<","<<point.y<<") \n";
    return os;
}

std::istream &operator>>(std::istream &input, Point &point) {
    char dummy;
    input >> point.x >> dummy >> point.y;
    return input;
}


