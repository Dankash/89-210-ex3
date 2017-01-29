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
#include "Tcp.h"
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
#include <tgmath.h>
#include "ThreadPool.h"

using namespace std;
char option[2];
int locationTripsFlag = 0;
bool sendingFlag = false;
//bool bfsFlag = false;
/**
 * Client data.
 * to send and recieve data.
 */
class ClientData  {
public:
    TaxiCenter* taxiCenter;
    list<Driver*> *drivers;
    Tcp* socket;
    int clientDescriptor;
    char cabSerialized[4096];
    string *locationSerialize;
    ClientData(Tcp* msocket,TaxiCenter* mtaxiCenter, list<Driver*> *mdrivers, char *mcabSerialized, int mclientDescriptor, string *mlocationSerialize) {
        taxiCenter = mtaxiCenter;
        drivers = mdrivers;
        socket = msocket;
        strcpy(cabSerialized, mcabSerialized);
        clientDescriptor = mclientDescriptor;
        locationSerialize = mlocationSerialize;
    }
};
/**
 * Trip data.
 * to send trip info to clients.
 */
class TripData {
public:
    Location* location;
    stack<Point> *path;
    Grid* grid;
    //list<Driver*>::iterator *it;
    Driver *driver;
    TripData(Grid *newGrid, Location* newLocation, stack<Point> *newPath, Driver* newIt)  {
        location =  newLocation;
        path = newPath;
        //it = newIt;
        driver = newIt;
        grid = newGrid;
    }
};


/**
 * taking details about driver in the input and creating new driver
 * @return new driver
 */
 

Driver* inputDriver(char* buffer) {
    Driver *driver = new Driver();

    int id, age, yoe, cabId;
    char dummy, marital;
    char* token;
    int i = 1;

    token = strtok (buffer,",|");
    while (token != NULL) {
        switch (i)
        {
            case 1:
                driver->setId(atoi(token));
                break;
            case 2:
                driver->setAge(atoi(token));
                break;
            case 3:
                driver->setMaritalStatus(token[0]);
                break;
            case 4:
                driver->setYearsOfExperience(atoi(token));
                break;
            case 5:
                driver->setCabId(atoi(token));
                break;
        }
        i++;
        token = strtok(NULL, ",|");
    }
    return driver;
}

/**
 * check if the input is number and positive
 * @param s - the string of th input
 * @return true if valid.
 */
bool isNumberAndPositive(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) {
        ++it;
    }

    return !s.empty() && it == s.end() && atoi(s.c_str()) >= 0;
}

/**
 * check if the input is double
 * @param str - the input string
 * @return true if it's double
 */
bool isDouble(const char* str)
{
    char* endptr = 0;
    strtod(str, &endptr);
    return !(*endptr != '\0' || endptr == str);
}
/**
 * taking details about trip in the input and creating new trip
 * @return new trip
 */
Trip* inputTrip() {
    Trip *trip = new Trip();
    int id, xStart, yStart, xEnd, yEnd, numOfPassengers;
    double tariff;
    int timeOfStart;
    char dummy;
    char* input;
    int counterTokens;
    int i;
    char* token;
    string str2;


        cin >> str2;
        input = (char *) str2.c_str();
        //std::count(input.beg, input.end, ",");
        counterTokens = 0;
        i = 0;
        token = strtok(input, ",");
        while (token != NULL) {

            if ( i ==  0) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    id = atoi(token);

            } else if ( i == 1) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    xStart = atoi(token);

            } else if ( i == 2) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    yStart = atoi(token);

            } else if ( i == 3) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    xEnd = atoi(token);

            } else if ( i == 4) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    yEnd = atoi(token);

            } else if ( i ==  5) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    numOfPassengers = atoi(token);

            } else if ( i == 6) {
                if (!isDouble(token)) {
                    return NULL;
                } else
                    sscanf(token, "%lf", &tariff);

            } else if ( i ==  7) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    timeOfStart = atoi(token);

            } else {
                return NULL;
            }

            i++;
            counterTokens++;
            token = strtok(NULL, ",");
        }

        if (i != 8)
            return NULL;




    trip->setRideId(id);
    trip->setStartX(xStart);
    trip->setStartY(yStart);
    trip->setEndX(xEnd);
    trip->setEndY(yEnd);
    trip->setNumberOfPassengers(numOfPassengers);
    trip->setFare(tariff);
    trip->setTimeOfStart(timeOfStart);
    return trip;
}
/**
 * taking details about cab in the input and creating new cab
 * @return new cab
 */
Cab* inputCab(std::list<string> &cabserialize) {
    Cab *cab;
    int id, type, i;
    char brand, color;
    char* token;
    char* input;
    string str2;

        cin >> str2;
        input = (char *) str2.c_str();
        i = 0;
        token = strtok(input, ",");
        while (token != NULL) {
            if (i == 0) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    id = atoi(token);
            } else if (i == 1) {
                std::string str(token);
                if (!isNumberAndPositive(str)) {
                    return NULL;
                } else
                    type = atoi(token);
            } else if (i == 2) {
                if ((std::string(token)).size() != 1  || (token[0] != 'H' && token[0] != 'S' && token[0] != 'T' && token[0] != 'F')) {
                    return NULL;
                } else
                    brand = token[0];
            } else if (i == 3) {
                if ((std::string(token)).size() != 1  || (token[0] != 'R' && token[0] != 'B' && token[0] != 'G' && token[0] != 'P')) {
                    return NULL;
                } else
                    color = token[0];
            } else {
                return NULL;
            }

            i++;
            token = strtok(NULL, ",");
        }
        if (i != 4)
            return NULL;


    string str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(type) + "," + brand
                 + "," + color + "|";
    cabserialize.push_back(str);
    if (type == 1)
        cab = new StandardCab(id, type, brand, color);
    else
        cab = new LuxuryCab(id, type, brand, color);
    return cab;
}

/**
 * Connect Grid and Calculate BFS for each client.
 * @param element - TripData.
 * @return .
 */
void* ConnectAndBFS(void* element) {
    TripData* tripData = (TripData*) element;
    Trip *trip = tripData->driver->getCab()->getTrip();

    ConnectGrid::connect(tripData->grid, tripData->location, tripData->grid->getRow(), tripData->grid->getCol());
    tripData->driver->getCab()->setTrip(trip);
    *(tripData->path) = BFS::bfs(tripData->grid ,tripData->driver->getCab()->getTrip()->getStartPoint(), tripData->driver->getCab()->getTrip()->getEndPoint());
    //bfsFlag = true;
    //pthread_exit(element);/////////////////////////////////////////////////////
}


// char* buffer, int size, int clientDescriptor
/**
 * Send the option input to all clients via tcp.
 * @param tcp.
 * @param sendingFlag  - determine if we should send the option.
 * @param clientSockets - client descriptors list.
 */
void distributeOption (Socket* tcp, bool &sendingFlag, list <int> clientSockets) {
    list<int>::iterator itStart;
    list<int>::iterator itEnd;
    itStart = clientSockets.begin();
    itEnd = clientSockets.end();
    sleep(1);
    if (sendingFlag) {
        while (itStart != itEnd) {
            (*tcp).sendData(option, (*(itStart)));
            std::advance(itStart, 1);
        }
    }
}
/**
 *
 * @param element
 * @return - sending and receiving data between server and clients.
 */
void* ConnectClient(void* element) {
    pthread_mutex_t driversMutex = PTHREAD_MUTEX_INITIALIZER;
    ClientData* clientData = (ClientData*) element;
    //int cabId;
    char buffer[4096];
    Driver* driver2;
    sendingFlag = true;
    clientData->socket->sendData("1", clientData->clientDescriptor);
    clientData->socket->receiveData(buffer, sizeof(buffer), clientData->clientDescriptor);
    pthread_mutex_lock(&driversMutex);
    driver2 = inputDriver(buffer);
    clientData->drivers->push_back(driver2);
    clientData->taxiCenter->assignCabToDriver();
    pthread_mutex_unlock(&driversMutex);
    clientData->socket->sendData(clientData->cabSerialized, clientData->clientDescriptor);

    while  (option[0] != '7') {

        if (option[0] == '9' && locationTripsFlag == 1) {
            clientData->socket->sendData("9", clientData->clientDescriptor);
            clientData->socket->receiveData(buffer, sizeof(buffer), clientData->clientDescriptor);
            clientData->socket->sendData(*(clientData->locationSerialize), clientData->clientDescriptor);

            //cout << "sent sirluzim ";
        }
    }
    pthread_exit(element);
}

/**
 *
 * @param grid - the grid.
 * @param point - the wanted point.
 * @return the location in the grid which has the same point as the argument has.
 */
Location* retLocationInGridByPoint(Grid* grid, Point point) {
    for (int i = 0; i < grid->getRow(); ++i) {
        for (int j = 0; j < grid->getCol(); ++j) {
            if (grid->getLocations()[i][j].getPoint() == point)
                return &(grid->getLocations()[i][j]);
        }
    }
    return NULL;

}

/**
 *
 * @return main function return 0.
 */
int main(int argc, char *argv[]) {
    Tcp tcp = Tcp(1, atoi(argv[1]));
    tcp.initialize();
    int currentTime = 0;
    int gridSize[2];
    int numOfObstacles;
    int i = 0;
    pthread_t thread;
    int numOfDrivers; //num of drivers to create
    std::list<Point> obstacles;
    list<int> clientSockets;
    char assignBuffer[7];
    std::list<Driver *> drivers;
    std::list<Cab *> cabs;
    std::list<string> cabserialize;
    TaxiCenter center = TaxiCenter(&drivers, &cabs);
    Point point = Point();
    std::list<Trip *> tripQueue;
    stack<Point> path;
    int driverId;
    Driver *driver;
    list<Driver *>::iterator it;
    //list <pthread_t> threads;
    char buffer[1024];
    char buffer2[1024];
    list<string>::iterator serializeIt;
    Driver *driver2;
    string locationSerialize;
    Location *loc;
    int clientDescriptor = 0;
    int j;
    bool checker = false;
    bool obstacklesChecker = false;
    Trip * iTrip;
    Cab * iCab;
    bool foundDriver = false;
    std::stack<Point> tempStack;
    Location* tempLocation;
    ThreadPool* pool= new ThreadPool(5);
    Job* job;


    while(!obstacklesChecker) {
        //the grid input
        while (!checker) {
            cin >> gridSize[0] >> gridSize[1];
            if (gridSize[0] > 0 && gridSize[1] > 0 && !cin.fail())
                checker = true;
            else
                cout << "-1" << endl;
            cin.clear();
            cin.ignore();
        }

        checker = false;
        while (!checker) {
            cin >> numOfObstacles;
            if (numOfObstacles >= 0 && !cin.fail())
                checker = true;
            else {
                cout << "-1" << endl;
                cin.clear();
                cin.ignore();
                break;
            }
            cin.clear();
            cin.ignore();
        }

        if (!checker) {
            continue;
        }

        checker = false;
        obstacklesChecker  = true;
        //creating obstacles if the num of them is bigger than 0.
        if (numOfObstacles > 0) {
            for (i = 0; i < numOfObstacles; i++) {
                while (!checker) {
                    cin >> point;
                    if (point.GetX() > 0 && point.GetY() > 0 && point.GetX() < gridSize[0] && point.GetY() < gridSize[1] && !cin.fail())
                        checker = true;
                    else {
                        cout << "-1" << endl;
                        checker = false;
                        obstacklesChecker = false;
                        break;
                    }
                }
                if (!obstacklesChecker)
                    break;
                obstacles.push_back(point);
                checker = false;
            }
        }
    }

    //creating locations for building a grid
    Location** locations = new Location*[gridSize[0]];
    for(int i = 0; i < gridSize[0]; ++i)
        locations[i] = new Location[gridSize[1]];
    for (int j = 0; j < gridSize[0]; ++j) {
        for (int i = 0; i < gridSize[1]; ++i) {
            locations[j][i].setParent(NULL);
            locations[j][i].setDistance(10000);
            locations[j][i].setPoint(Point(j,i));
        }
    }
    //creating a grid
    Grid* grid = new Grid(locations, obstacles, gridSize[0], gridSize[1]);
    //menu's option of the user
    cin>>option;

    while ( option[0] != '7' ) {
        if(option[1] == '\0') {
                switch (option[0]) {
                //creating a new driver
                case '1':
                    cin >> numOfDrivers;
                        if(numOfDrivers <= 0 || cin.fail()) {
                            cout << "-1";
                            cin.clear();
                            cin.ignore();
                            break;
                        }
                    for (j = 0; j < numOfDrivers; ++j) {
                        clientDescriptor = tcp.acceptOneClient();
                        clientSockets.push_back(clientDescriptor);
                        ClientData *clientData = new ClientData(&tcp, &center, &drivers, buffer2, clientDescriptor,
                                                                &locationSerialize);
                        pthread_create(&thread, NULL, ConnectClient, clientData);
                    }

                    //sendingFlag = true;
                    break;
                    //creating new trip
                case '2':
                    iTrip = inputTrip();

                    if (iTrip != NULL) {
                        tempLocation = retLocationInGridByPoint(grid, iTrip->getStartPoint());
                        ConnectGrid::connect(grid, tempLocation, grid->getRow(), grid->getCol());

                        if (retLocationInGridByPoint(grid, iTrip->getEndPoint())->getParent() == NULL) {
                            cout << "-1" << endl;
                            break;
                        }
                        tripQueue.push_front(iTrip);
                    }
                    else
                        cout << "-1" <<endl;
                    break;
                    //creating new cab
                case '3':
                    iCab = inputCab(cabserialize);
                    if (iCab != NULL) {
                        cabs.push_back(iCab);
                        serializeIt = cabserialize.begin();
                        for (i = 0; i < cabserialize.size(); ++i) {
                            strcpy(buffer2, (*(serializeIt)).c_str());
                            std::advance(serializeIt, 1);
                        }
                    } else
                        cout << "-1" <<endl;

                    break;
                    //printing location of a driver according to id
                case '4':
                    cin >> driverId;
                    it = drivers.begin();
                    for (int i = 0; i < drivers.size(); ++i) {
                        if ((*it)->getId() == driverId) {
                            cout << (*it)->getCab()->getLocation().getPoint();
                            foundDriver = true;
                        }
                        std::advance(it, 1);
                    }
                    if (!foundDriver)
                        cout << "-1" << endl;

                    foundDriver = false;

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
                    locationTripsFlag = 0;
                    it = drivers.begin();
                    //assign trip to driver
                    if (!tripQueue.empty() /*&& strcmp(assignBuffer, "assign") == 0*/) {
                        distributeOption(&tcp, sendingFlag, clientSockets);
                        for (int i = 0; i < drivers.size(); ++i) {
                            if ((*it)->getCab()->getTrip() == NULL && !tripQueue.empty() &&
                                (*it)->getCab()->getLocation().getPoint() == tripQueue.front()->getStartPoint()) {
                                (*it)->getCab()->setTrip(tripQueue.front());
                                tripQueue.pop_front();
                            }
                            std::advance(it, 1);
                        }

                    } else if ((*(it))->getCab()->getTrip() != NULL) { /////////////////////////////////////////////// before: else
                        for (int i = 0; i < drivers.size(); ++i) {
                            pthread_t threadTrip;
                            loc = new Location((*(it))->getCab()->getTrip()->getStartPoint(), NULL);
                            TripData *tripData = new TripData(grid, loc, &path, *(it));
                            //pthread_create(&threadTrip, NULL, ConnectAndBFS, tripData);
                            job = new Job(ConnectAndBFS, tripData);
                            pool->addJob(job);

                            //pthread_join(threadTrip, NULL);

                            while (!pool->getJobs_queue().empty()) {

                             }

                            if (!tripData->path->empty()) {
                                if ((*(it))->getCab()->getTrip()->getTimeOfStart() == currentTime) {
                                    if ((*(it))->getCab()->getType() == 2 &&
                                        path.size() > 1) { // luxury cab drives through 2 points each time
                                        (*it)->getCab()->Drive(path.top());
                                        (*(it))->getCab()->getTrip()->setStartPoint(path.top());
                                        tripData->path->pop();
                                    }
                                    (*it)->getCab()->Drive(path.top());

                                    (*(it))->getCab()->getTrip()->setStartPoint(path.top());
                                    tripData->path->pop();
                                    locationSerialize = "";
                                    locationSerialize += boost::lexical_cast<string>((*(it))->getCabId()) + "," +
                                                         boost::lexical_cast<string>(
                                                                 (*it)->getCab()->getLocation().getPoint()) +
                                                         "," + boost::lexical_cast<string>(
                                            (*it)->getCab()->getLocation().getDistance()) + "|";
                                    (*it)->getCab()->getTrip()->setTimeOfStart(
                                            (*it)->getCab()->getTrip()->getTimeOfStart() + 1);
                                    if (tripData->path->empty())
                                        (*it)->getCab()->setTrip(NULL);

                                }

                            } else {
                                (*it)->getCab()->setTrip(NULL);
                            }
                            std::advance(it, 1);
                        }
                        locationTripsFlag = 1;
                    }
                    currentTime++;

                    break;
                default:
                    cout << "-1" << endl;
                    break;
            }
        } else {
            cout << "-1" << endl;
        }
        cin>>option;
        if (sendingFlag == true && option[0] != '9')
            distributeOption(&tcp, sendingFlag, clientSockets);
    }

    // support more than one client?

    //pthread_join(thread, NULL);
    pool->terminate();

    return 0;
}
