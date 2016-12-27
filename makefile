#blumend2 204326755 gispana 305759383
all: ex3

ex3: main.o BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o
	g++ main.o BFS.o Grid.o ConnectGrid.o Location.o Point.o Cab.o Driver.o Listener.o LuxuryCab.o Notifier.o Passenger.o StandardCab.o TaxiCenter.o TransportationMap.o Trip.o Neighbors.o

main.o: main.cpp
	g++ -c main.cpp

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
