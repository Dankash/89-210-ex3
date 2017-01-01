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

void assignCabToDriver(Driver *driver, std::list<string> &cabserialize) {



}

int main(int argc, char *argv[]) {
    char dummy;
    int id, age, yoe, cabId;
    char maritalStatus;
    std::cout << "Hello, from client" << std::endl;

    cout << argv[1] << endl;
    Udp udp(0, atoi(argv[1]));
    udp.initialize();

    cin >> id >> dummy >> age >> dummy >> maritalStatus >> dummy >> yoe >> dummy >> cabId;
    Driver *driver = new Driver(id, age, maritalStatus, yoe, cabId);
    string str = boost::lexical_cast<string>(id) + "," + boost::lexical_cast<string>(age) + "," +
                 maritalStatus + "," + boost::lexical_cast<string>(yoe) + "," + boost::lexical_cast<string>(cabId);

    char buffer[1024];
    udp.sendData("hello");
    udp.reciveData(buffer, sizeof(buffer));
    cout << buffer << endl;


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