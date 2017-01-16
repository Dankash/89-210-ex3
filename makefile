all: server.out client.out 

server.out: BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o Socket.o Tcp.o Udp.o Server.o
	g++ BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o Socket.o Tcp.o Udp.o Server.o -o server.out

client.out: BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o Socket.o Tcp.o Udp.o Client.o
	g++ BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o Socket.o Tcp.o Udp.o Client.o -o client.out


Client.o: Client.cpp
	g++ -c Client.cpp

Server.o: Server.cpp
	g++ -c Server.cpp

BFS.o: BFS.cpp
	g++ -c BFS.cpp

Grid.o: Grid.cpp
	g++ -c Grid.cpp

ConnectGrid.o: ConnectGrid.cpp
	g++ -c ConnectGrid.cpp

Location.o: Location.cpp
	g++ -c Location.cpp

Point.o: Point.cpp
	g++ -c Point.cpp

Cab.o: Cab.cpp
	g++ -c Cab.cpp

Driver.o: Driver.cpp
	g++ -c Driver.cpp

Listener.o: Listener.cpp
	g++ -c Listener.cpp

LuxuryCab.o: LuxuryCab.cpp
	g++ -c LuxuryCab.cpp

Notifier.o: Notifier.cpp
	g++ -c Notifier.cpp

Passenger.o: Passenger.cpp
	g++ -c Passenger.cpp

StandardCab.o: StandardCab.cpp
	g++ -c StandardCab.cpp

TaxiCente.o: TaxiCenter.cpp
	g++ -c TaxiCenter.cpp

TransportationMap.o: TransportationMap.cpp
	g++ -c TransportationMap.cpp

Trip.o: Trip.cpp
	g++ -c Trip.cpp

Neighbors.o: Neighbors.cpp
	g++ -c Neighbors.cpp

Socket.o: Socket.cpp
	g++ -c Socket.cpp

Tcp.o: Tcp.cpp
	g++ -c Tcp.cpp

Udp.o: Udp.cpp
	g++ -c Udp.cpp

clean:
	rm -f *.o a.out

