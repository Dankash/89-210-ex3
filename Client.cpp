#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
#include "Udp.h"
#include <unistd.h>
#include "Driver.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Tcp.h"
#include <boost/lexical_cast.hpp>

using namespace std;

/**
 *
 * @param locationserialize - the serialized location.
 * @param cabs - list of cabs.
 */
void locationsDeserialize(char *locationserialize, std::list<Cab*> &cabs) {
    Location location;
    char* token1;
    char *token2;
    int cabId;
    Point point;
    Cab *cab;
    int i = 1;
    token1 = strtok(locationserialize, "|");
    while (token1 != NULL) {
        i = 1;
        token2 = strtok(token1, ",");
        while (token2 != NULL) {
            switch (i) {
                case 1:
                    cabId = (atoi(token2));
                    break;
                case 2:
                    point.SetX(token2[1] - '0');
                    break;
                case 3:
                    point.SetY(token2[0] - '0');
                    location.setPoint(point);
                    break;
                case 4:
                    location.setDistance(atoi(token2));
                    break;
            }
            i++;
            token2 = strtok(NULL, ",");
        }
        token1 = strtok(NULL, "|");

        location.setParent(NULL);
        list<Cab *>::iterator cabItStart;//update the matching cab's location
        list<Cab *>::iterator cabItEnd;
        cabItStart = cabs.begin();
        cabItEnd = cabs.begin();
        advance(cabItEnd, cabs.size() - 1);
        for (i = 0; i < cabs.size(); ++i) {
            cab = *(cabItStart);
            if (cab->getId() == cabId) {
                cab->setLocation(location);
            }
            advance(cabItStart, 1);
        }
    }


}
/**
 * desrialized cab and push it into cabs list.
 * @param buff - the serializes cab.
 * @param cabs - the list of the cabs.
 */
void cabsDeserialize(char *buff, std::list<Cab *> &cabs) {
    int id;
    int  type;
    char brand;
    char color;
    //StandardCab *c;
    LuxuryCab* d;
    char *token;
    char *token2;
    int i = 1;
    Cab* cab;

    token = strtok(buff, "|");
    while (token != NULL) {
        token2 = strtok(token, ",");
        while (token2 != NULL) {
            switch (i) {
                case 1:
                    id = atoi(token2);
                    break;
                case 2:
                    type = atoi(token2);
                    break;
                case 3:
                    brand = token2[0];
                    break;
                case 4:
                    color = token2[0];
                    break;
            }
            i++;
            token2 = strtok(NULL, ",");
        }
        token = strtok(NULL, "|");
    }

    if (type == 1) {
        StandardCab *c = new StandardCab(id, type, brand, color);
        cab = (Cab*) c;
        cabs.push_back(cab);
    } else {
        d = new LuxuryCab(id, type, brand, color);
        cab = (Cab*) d;
        cabs.push_back(cab);
    }


}
/**
 * assign cabs to matched drivers.
 * @param drivers - list of drivers.
 * @param cabs - list of cabs.
 */
void assignCabsToDrivers(std::list<Driver *> &drivers, std::list<Cab *> &cabs) {
    int i, j;
    list<Cab *>::iterator cabItStart;
    list<Cab *>::iterator cabItEnd;
    cabItStart = cabs.begin();
    cabItEnd = cabs.begin();
    advance(cabItEnd, cabs.size() - 1);
    list<Driver *>::iterator drItStart;
    list<Driver *>::iterator drItEnd;
    drItStart = drivers.begin();
    drItEnd = drivers.begin();
    advance(drItEnd, drivers.size() - 1);
    for (i = 0; i < cabs.size(); i++) {
        for (j = 0; j < drivers.size(); j++) {
            Driver *driver = *drItStart;
            Cab *cab = *cabItStart;
            if (cab->getId() == driver->getCabId()) {
                driver->setCab(cab);
            }
            if (drItStart != drItEnd)
                advance(drItStart, 1);
        }
        if (cabItStart != cabItEnd)
            advance(cabItStart, 1);
    }
}

/**
 *
 * @param argc - number of arguments.
 * @param argv -  the arguments.
 * @return runs the program and return  0.
 */
int main(int argc, char *argv[]) {
    char dummy;
    int id, age, yoe, cabId;
    char maritalStatus;
    int case9Counter = 0;//the first time of case 9 is diffrent
    std::list<Cab *> cabs;
    std::list<Driver *> drivers;
    char locationserialize[100];
    int clientDescriptor;
    Driver *driver;
    string str;
    Tcp tcp = Tcp(0, atoi(argv[2]));
    tcp.initialize();
    char option[2];
    char buffer[1024];
    tcp.receiveData(option, sizeof(option), clientDescriptor);
    while (option[0] != '7') {
        switch (option[0]) {
            case '1':
                cin >> id >> dummy >> age >> dummy >> maritalStatus >> dummy >> yoe >> dummy >> cabId;
                driver = new Driver(id, age, maritalStatus, yoe, cabId);
                drivers.push_back(driver);
                str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(age) + "," +
                      maritalStatus + "," + boost::lexical_cast<string>(yoe) + "," +
                      boost::lexical_cast<string>(cabId) + "|";
                tcp.sendData(str, clientDescriptor);
                tcp.receiveData(buffer, sizeof(buffer), clientDescriptor);
                cabsDeserialize(buffer, cabs);
                assignCabsToDrivers(drivers, cabs);
                break;
            case '2': case9Counter = 0;
                break;
            case '9':
                /*if(case9Counter == 0) ////////////////////////////////////////////
                    tcp.sendData("assign", clientDescriptor); ///////////////////////////////
                else
                    tcp.sendData("dont", clientDescriptor);*/ ////////////////////////////////
                if (case9Counter != 0) {
                    tcp.sendData("hi", 0);
                    tcp.receiveData(locationserialize, 100, clientDescriptor);
                    locationsDeserialize(locationserialize, cabs);
                }
                case9Counter++;

            default:
                break;
        }
        tcp.receiveData(option, sizeof(option), clientDescriptor);

    }
    return 0;
}
