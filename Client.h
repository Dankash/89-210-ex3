

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class Client {
public:
	Client(char* ip, int port, string name);
	void Connect();
	virtual ~Client();
private:
	char* ip;
	int port;
	int client_socket;
	struct sockaddr_in connection_details;
	bool connected;
	string name;
};

#endif /* CLIENT_CLIENT_H_ */
