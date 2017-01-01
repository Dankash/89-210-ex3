#include "LuxuryCab.h"

LuxuryCab::LuxuryCab(int id, int type, char brand, char color)
        : Cab::Cab(id, type, brand, color) {
    setFee(2);
}

void LuxuryCab::Drive() {
    location.setPoint(trip->getEndPoint());
}

BOOST_CLASS_EXPORT(Cab)