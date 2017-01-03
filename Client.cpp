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
#include <boost/lexical_cast.hpp>

using namespace std;

/*void save() {
    ofstream file("archive.txt");
    boost::archive::text_oarchive oa(file);
    std::string s = "Hello World\n";
    oa<<s;
}

void load() {
    ifstream file("archive.txt");
    boost::archive::text_iarchive ia(file);
    string s;
    ia >> s;
    cout << s <<endl;
}*/
void locationsDeserialize(char *locationserialize, std::list<Cab*> &cabs) {
    Location location;
    char *token;
    int cabId;
    Point point;
    int i = 0;
    token = strtok(locationserialize, ",");
    while (token != NULL) {
        switch (i) {
            case 1:
                cabId = (atoi(token));
                break;
            case 2:
                point.SetX(token[0]);
                point.SetY(token[1]);
                location.setPoint(point);
                break;
            case 3:
                location.setDistance(atoi(token));
                break;
        }
        location.setParent(NULL);
        i++;
        token = strtok(token, ",");
        list<Cab *>::iterator cabItStart;//update the matching cab's location
        list<Cab *>::iterator cabItEnd;
        cabItStart = cabs.begin();
        cabItEnd = cabs.begin();
        advance(cabItEnd, cabs.size() - 1);
        for (i = 0; i < cabs.size(); ++i) {
            Cab *cab = *(cabItStart);
            if (cab->getId() == cabId) {
                cab->setLocation(location);
            }
            advance(cabItStart, 1);
        }
    }
}
    void cabsDeserialize(char *buff, std::list<Cab *> &cabs) {
        Cab *cab;
        char *token;
        char *token2;
        int i = 0;

        token = strtok(buff, "|");
        while (token != NULL) {
            token2 = strtok(token, ",");
            while (token2 != NULL) {
                switch (i) {
                    case 1:
                        cab->setId(atoi(token));
                        break;
                    case 2:
                        cab->setType(atoi(token));
                        break;
                    case 3:
                        cab->setBrand(token[0]);
                        break;
                    case 4:
                        cab->setColor(token[0]);
                        break;
                }
                i++;
                token2 = strtok(token, ",");
            }
            cabs.push_back(cab);
            token = strtok(buff, "|");
        }
    }

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


    int main(int argc, char *argv[]) {
        char dummy;
        int id, age, yoe, cabId;
        char maritalStatus;
        std::cout << "Hello, from client" << std::endl;
        std::list<Cab *> cabs;
        std::list<Driver *> drivers;
        char locationserialize[100];
        Driver *driver;
        string str;
        cout << argv[1] << endl;
        Udp udp(0, atoi(argv[1]));
        udp.initialize();
        char option[2];
        char buffer[1024];
        cout << "before recieving" << endl;
        udp.reciveData(option, sizeof(option));
        cout << "after recieving: " << option <<endl;
        while (option[0] != '7') {
            switch (option[0]) {
                case '1':
                    cin >> id >> dummy >> age >> dummy >> maritalStatus >> dummy >> yoe >> dummy >> cabId;
                    driver = new Driver(id, age, maritalStatus, yoe, cabId);
                    str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(age) + "," +
                                 maritalStatus + "," + boost::lexical_cast<string>(yoe) + "," +
                                 boost::lexical_cast<string>(cabId);
                    udp.sendData(buffer);
                    udp.reciveData(buffer, sizeof(buffer));
                    cout << buffer << endl;
                    cabsDeserialize(buffer, cabs);
                    assignCabsToDrivers(drivers, cabs);
                    break;
                case '9':
                    for (int i = 0; i < drivers.size(); ++i) {
                        udp.reciveData(locationserialize, 100);
                        locationsDeserialize(locationserialize, cabs);
                    }
                default:
                    break;
            }
            udp.reciveData(option, 2);

        }
        return 0;
    }
/*
int main() {

    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    char data[] = "hello";
    int data_len = sizeof(data);

    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The server sent: " << buffer << endl;

    close(sock);

    return 0;
}*/