#include "LuxuryCab.h"

LuxuryCab::LuxuryCab(int id, int type, char brand, char color)
        : Cab::Cab(id, type, brand, color) {
    setFee(2);
}

void LuxuryCab::Drive(Point newPoint) {
    location.setPoint(newPoint);
}
