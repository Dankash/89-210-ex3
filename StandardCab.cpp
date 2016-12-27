#include "StandardCab.h"

StandardCab::StandardCab(int id, int type, char brand, char color)
        : Cab::Cab(id, type, brand, color)  {
    setFee(1);
}



void StandardCab::Drive() {
    location.setPoint(trip->getEndPoint());
}
