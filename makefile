all: Server.out Client.out 

Server.out: Server.o BFS.o Grid.o StandardCab.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Neighbors.o Location.o TransportationMap.o ConnectGrid.o
	g++ -std=c++0x -pthread Server.o BFS.o Grid.o Neighbors.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Location.o Socket.o Tcp.o ConnectGrid.o  -lboost_serialization -I. -o Server.out

Client.out: Client.o BFS.o Grid.o StandardCab.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Neighbors.o Location.o TransportationMap.o ConnectGrid.o
	g++ -std=c++0x -pthread Client.o BFS.o Grid.o Neighbors.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Location.o Socket.o Tcp.o ConnectGrid.o  -lboost_serialization -I. -o Client.out

Server.o: Server.cpp
	g++ -std=c++0x -c -pthread Server.cpp

Client.o: Client.cpp
	g++ -std=c++0x -c -pthread Client.cpp

BFS.o: BFS.cpp BFS.h
	g++ -std=c++0x -c -pthread BFS.cpp

Grid.o: Grid.cpp Grid.h
	g++ -std=c++0x -c -pthread Grid.cpp

ConnectGrid.o: ConnectGrid.cpp ConnectGrid.h
	g++ -std=c++0x -c -pthread ConnectGrid.cpp

StandardCab.o: StandardCab.cpp StandardCab.h
	g++ -std=c++0x -c -pthread StandardCab.cpp

Point.o: Point.cpp Point.h
	g++ -std=c++0x -c -pthread Point.cpp

Cab.o: Cab.cpp Cab.h
	g++ -std=c++0x -c -pthread Cab.cpp

Driver.o: Driver.cpp Driver.h
	g++ -std=c++0x -c -pthread Driver.cpp

Listener.o: Listener.cpp Listener.h
	g++ -std=c++0x -c -pthread 	Listener.cpp

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h
	g++ -std=c++0x -c -pthread LuxuryCab.cpp

Notifier.o: Notifier.cpp Notifier.h
	g++ -std=c++0x -c -pthread Notifier.cpp

Passenger.o: Passenger.cpp Passenger.h
	g++ -std=c++0x -c -pthread Passenger.cpp

StandardCab.o: StandardCab.cpp StandardCab.h
	g++ -std=c++0x -c -pthread StandardCab.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h
	g++ -std=c++0x -c -pthread TaxiCenter.cpp

TransportationMap.o: TransportationMap.cpp TransportationMap.h
	g++ -std=c++0x -c -pthread TransportationMap.cpp

Trip.o: Trip.cpp Trip.h
	g++ -std=c++0x -c -pthread Trip.cpp

Socket.o: Socket.cpp Socket.h
	g++ -std=c++0x -c -pthread Socket.cpp

Tcp.o: Tcp.cpp Tcp.h
	g++ -std=c++0x -c -pthread Tcp.cpp

Location.o: Location.cpp Location.h
	g++ -std=c++0x -c -pthread Location.cpp

Neighbors.o: Neighbors.cpp Neighbors.h
	g++ -std=c++0x -c -pthread Neighbors.cpp

clean:
	rm -f *.o a.out

