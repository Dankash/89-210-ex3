

#include "Client.h"

Client::Client(char* ip, int port, string name) {
	this->ip = ip;
	this->port = port;
	this->client_socket = -1;
	this->connected = false;
	this->name = name;
}

void Client::Connect()
{
	// Init socket
	this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(this->client_socket >= 0){
		// Memset the connection details
		memset(&this->connection_details, 0, sizeof(this->connection_details));
		this->connection_details.sin_family = AF_INET;
		this->connection_details.sin_addr.s_addr = inet_addr(ip);
		this->connection_details.sin_port = htons(port);
		// Connect to a server
		if (connect(this->client_socket,
				(struct sockaddr*)&this->connection_details, sizeof(this->connection_details)) >= 0)
			this->connected = true;
	}
	// While we're connected
	while (this->connected)
	{
		// Get a message from user
		string msg;
		getline(cin, msg);
		// '7' Means close the connection
		if (msg == "7")
		{
			this->connected = false;
		}
		else
		{
			// Add the name to the message
			msg = this->name + ": " + msg;
			// Convert to char*
			const char* buffer = msg.c_str();
			try
			{
				// Send the message to the server
				int bytes = send(this->client_socket, buffer, msg.length(), 0);
				if (bytes >= 0)
					cout << ">> Message was sent ---> " << msg << endl;
				else
					cout << ">> Failed to send the message." << endl;
			}
			catch (...)
			{
				cout << ">> Error." << endl;
			}
		}
	}
}
Client::~Client() {
	close(this->client_socket);
}

