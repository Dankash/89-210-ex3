#include <iostream>
#include "ConnectGrid.h"
#include <queue>
#include <iterator>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <cstring>
#include "BFS.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
using namespace std;

/**
 * taking details about driver in the input and creating new driver
 * @return new driver
 */
Driver* inputDriver() {
    Driver *driver = new Driver();
    int id, age, yoe, cabId;
    char dummy, marital;
    cin >> id >> dummy >> age >> dummy >> marital >> dummy >> yoe >> dummy >> cabId;
    driver->setId(id);
    driver->setAge(age);
    driver->setMaritalStatus(marital);
    driver->setYearsOfExperience(yoe);
    driver->setCabId(cabId);
    return driver;
}

/**
 * taking details about trip in the input and creating new trip
 * @return new trip
 */
Trip* inputTrip() {
        Trip *trip = new Trip();
        int id, xStart, yStart, xEnd, yEnd, numOfPassengers;
        double tariff;
        char dummy;
        cin >> id >> dummy >> xStart >> dummy >> yStart >> dummy >> xEnd >> dummy >> yEnd >> dummy >>
                                                               numOfPassengers >> dummy >> tariff;
        trip->setRideId(id);
        trip->setStartX(xStart);
        trip->setStartY(yStart);
        trip->setEndX(xEnd);
        trip->setEndY(yEnd);
        trip->setNumberOfPassengers(numOfPassengers);
        trip->setFare(tariff);
        return trip;
    }

/**
 * taking details about cab in the input and creating new cab
 * @return new cab
 */
Cab* inputCab() {
    Cab *cab;
    int id, type;
    char brand, color, dummy;
    cin >> id >> dummy >> type >> dummy >> brand >> dummy >> color;
    if (type == 1)
        cab = new StandardCab(id, type, brand, color);
    else
        cab = new LuxuryCab(id, type, brand, color);
    return cab;
}


int main(int argc, char* argv[]) {
    int gridSize[2];
    int numOfObstacles;int i = 0;
    std::list<Point> obstacles;
    std::list<Driver*> drivers;
    std::list<Cab*> cabs;
    TaxiCenter center = TaxiCenter(&drivers, &cabs);
    Point point = Point();
    int option;
    std::queue<Trip*> tripQueue;
    int driverId;
    Driver *driver;
    list<Driver*>::iterator it;
    //the grid input
    cin >> gridSize[0] >> gridSize[1];
    cin >> numOfObstacles;
    //creating obstacles if the num of them is bigger than 0.
    if(numOfObstacles > 0) {
        for (i = 0; i < numOfObstacles; i++) {
            cin >> point;
            obstacles.push_back(point);
        }
    }
    //creating locations for building a grid
    Location** locations = new Location*[gridSize[0]];
    for(int i = 0; i < gridSize[0]; ++i)
        locations[i] = new Location[gridSize[1]];
    for (int j = 0; j < gridSize[0]; ++j) {
        for (int i = 0; i < gridSize[1]; ++i) {
            locations[j][i].setParent(NULL);
            locations[j][i].setDistance(1000);
            locations[j][i].setPoint(Point(j,i));
        }
    }
    //creating a grid
    Grid grid = Grid(locations, obstacles, gridSize[0], gridSize[1]);
    //menu's option of the user
    cin>>option;
    while ( option != 7 ) {
        switch (option)  {
            //creating a new driver
            case 1:
                driver = inputDriver();
                drivers.push_back(driver);
                //assign cab to driver
                center.assignCabToDriver();
                break;
                //creating new trip
            case 2:
                tripQueue.push(inputTrip());
                break;
                //creating new cab
            case 3:
                cabs.push_back(inputCab());
                break;
                //printing location of a driver according to id
            case 4:
                cin >> driverId;
                it = drivers.begin();
                for (int i = 0; i < drivers.size(); ++i) {
                    if ((*it)->getId() == driverId) {
                        cout<<(*it)->getCab()->getLocation().getPoint();
                    }
                    std::advance(it, 1);
                }
                break;
                //all the drivers are driving to their destination point
            case 6:
                it = drivers.begin();
                //assign trip to driver
                for (int i = 0; i < drivers.size(); ++i) {
                    if ((*it)->getCab()->getTrip() == NULL && !tripQueue.empty()) {
                        (*it)->getCab()->setTrip(tripQueue.front());
                        tripQueue.pop();
                    }
                    std::advance(it, 1);
                }
                it = drivers.begin();
                //making driver drive
                for (int i = 0; i < drivers.size(); ++i) {
                    (*it)->getCab()->Drive();
                    (*it)->getCab()->setTrip(NULL);
                    std::advance(it, 1);
                }
                break;
        }
        cin>>option;
    }
    return 0;
}