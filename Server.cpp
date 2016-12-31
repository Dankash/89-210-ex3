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
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;

/**
 * taking details about driver in the input and creating new driver
 * @return new driver
 */
Driver* inputDriver(char* buffer) {
    Driver *driver = new Driver();

    int id, age, yoe, cabId;
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
    }
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
Cab* inputCab(std::list<string> &cabserialize) {
    Cab *cab;
    int id, type;
    char brand, color, dummy;
    cin >> id >> dummy >> type >> dummy >> brand >> dummy >> color;

    string str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(type) + "," + brand + color + "|";
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
    int currentTime = 0;
    int gridSize[2];
    int numOfObstacles;
    int i = 0;
    std::list<Point> obstacles;
    std::list<Driver*> drivers;
    std::list<Cab*> cabs;
    std::list<string> cabserialize;
    TaxiCenter center = TaxiCenter(&drivers, &cabs);
    Point point = Point();
    char option[2];
    std::queue<Trip*> tripQueue;
    stack<Point> path;
    int driverId;
    Driver *driver;
    list<Driver*>::iterator it;
    char buffer[1024];
    char buffer2[1024];
    list<string>::iterator serializeIt;
    Driver *driver2;
    string locationSerialize;
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

    /*boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);*/
    //menu's option of the user
    cin>>option;
    udp.sendData(option[0]+"");
    while ( option[0] != 7 ) {
        switch (option[0]) {
            //creating a new driver
            case '1':
                int cabId;
                udp.reciveData(buffer, sizeof(buffer));
                driver = inputDriver(buffer);
                //ia >> driver;
                drivers.push_back(driver2);
                center.assignCabToDriver();
                udp.sendData(buffer2);
//                cabId = driver->getCabId();

                break;
                //creating new trip
            case '2': {
                tripQueue.push(inputTrip());
            }
                break;
                //creating new cab
            case '3':
                cabs.push_back(inputCab(cabserialize));
                serializeIt = cabserialize.begin();
                for (i = 0; i < cabserialize.size(); ++i) {
                    strcpy(buffer2, (*(serializeIt)).c_str());
                    std::advance(serializeIt, 1);
                }

                break;
                //printing location of a driver according to id
            case '4':
                cin >> driverId;
                it = drivers.begin();
                for (int i = 0; i < drivers.size(); ++i) {
                    if ((*it)->getId() == driverId) {
                        cout << (*it)->getCab()->getLocation().getPoint();
                    }
                    std::advance(it, 1);
                }

                break;
                //all the drivers are driving to their destination point
            case '6':
                /*it = drivers.begin();
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
                }*/

                break;
            case '9':

                it = drivers.begin();
                //assign trip to driver
                if (!tripQueue.empty()) {
                    for (int i = 0; i < drivers.size(); ++i) {
                        if ((*it)->getCab()->getTrip() == NULL && !tripQueue.empty()){
                            (*it)->getCab()->setTrip(tripQueue.front());
                            tripQueue.pop();
                        }
                        std::advance(it, 1);
                    }
                } else {
                    for (int i = 0; i < drivers.size(); ++i) {
                        path = BFS::bfs(grid,(*(it))->getCab()->getTrip()->getStartPoint(), (*(it))->getCab()->getTrip()->getEndPoint());
                        if(!path.empty()) {
                            if ((*(it))->getCab()->getTimeOfStart() == currentTime) {
                                if ((*(it))->getCab()->getType() == 2) // luxury cab drives through 2 points each time
                                    (*it)->getCab()->Drive(path.top());
                                (*it)->getCab()->Drive(path.top());
                                (*it)->getCab()->setTrip(NULL);
                                locationSerialize = boost::lexical_cast<string>((*(it))->getCabId()) + "," +
                                                    boost::lexical_cast<string>(
                                                            (*it)->getCab()->getLocation().getPoint()) +
                                                    "," + boost::lexical_cast<string>(
                                        (*it)->getCab()->getLocation().getDistance());
                                path.pop();
                                (*it)->getCab()->setTimeOfStart((*it)->getCab()->getTimeOfStart() + 1);
                                std::advance(it, 1);

                            }
                            udp.sendData(locationSerialize);
                        }

                    }

                }
                currentTime++;

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