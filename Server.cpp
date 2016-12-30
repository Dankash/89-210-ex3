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
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Udp.h"
#include <unistd.h>
#include <boost/lexical_cast.hpp>
using namespace std;




/**
 * taking details about driver in the input and creating new driver
 * @return new driver
 */
Driver* inputDriver(/*char* buffer*/) {
    Driver *driver = new Driver();

    cin >> *driver;

    /*int id, age, yoe, cabId;
    char dummy, marital;
    char* token;
    int i = 0;

    token = strtok (buffer,",");

    while (token!= NULL) {
        switch (i)
        {
            case 1:
                driver->setId(atoi(token));
                break;
            case 2:
                driver->setAge(atoi(token));
                break;
            case 3:
                driver->setMaritalStatus(buffer[0]);
                break;
            case 4:
                driver->setYearsOfExperience(atoi(token));
                break;
            case 5:
                driver->setCabId(atoi(token));
                break;
        }
        i++;
        token = strtok(buffer, ",");
    }*/
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
Cab* inputCab(std::list<char*> &cabserialize) {
    Cab *cab;
    int id, type;
    char brand, color, dummy;
    //cin >> id >> dummy >> type >> dummy >> brand >> dummy >> color;
    //cin
    string str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(type) + "," + brand + color;
    cabserialize.push_back(str);
    if (type == 1)
        cab = new StandardCab(id, type, brand, color);
    else
        cab = new LuxuryCab(id, type, brand, color);
    return cab;
}

int main() {
    std::cout << "Hello, from server" << std::endl;

    Udp udp(1, 5555);
    udp.initialize();

    int gridSize[2];
    int numOfObstacles;int i = 0;
    std::list<Point> obstacles;
    std::list<Driver*> drivers;
    std::list<Cab*> cabs;
    std::list<char*> cabserialize;
    TaxiCenter center = TaxiCenter(&drivers, &cabs);
    Point point = Point();
    int option;
    std::queue<Trip*> tripQueue;
    int driverId;
    Driver *driver;
    list<Driver*>::iterator it;
    char buffer[1024];
    char buffer2[1024];
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
                udp.reciveData(buffer, sizeof(buffer));
                Driver *driver;
                driver = inputDriver(/*buffer*/);
                drivers.push_back(driver);
                center.assignCabToDriver();

                break;
                //creating new trip
            case 2:
                tripQueue.push(inputTrip());
                break;
                //creating new cab
            case 3:
                cabs.push_back(inputCab(cabserialize));
                list<char*>::iterator serializeIt;
                serializeIt = cabserialize.begin();
                for(i = 0; i < cabserialize.size(); ++i) {
                    strcpy(buffer, serializeIt);
                    std::advance(serializeIt, 1);
                }
                udp.sendData(buffer);
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


//
//    usleep(5000);
    Udp udp2(1, 5554);
    udp2.initialize();


    udp2.reciveData(buffer2, sizeof(buffer2));
    cout << buffer2 << endl;
    udp2.sendData("sup?");



    // support more than one client?
    return 0;
}


/*
int main() {

    const int server_port = 5555;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);


    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The client sent: " << buffer << endl;
    strcpy(buffer,"yanai the king!");


    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    close(sock);

    return 0;
}
*/




/*int main(int argc, char* argv[]) {
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
}*/