cmake_minimum_required(VERSION 3.3)
project(89-210-ex3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
#add_subdirectory(lib/googletest-master)
#add_subdirectory(sockets)
#include_directories(lib/googletest-master/googletest/include)
#include_directories(lib/googletest-master/googlemock/include)
set(SOURCE_FILES Server.cpp Point.cpp Point.h Location.cpp Location.h Grid.cpp Grid.h ConnectGrid.cpp ConnectGrid.h Neighbors.cpp Neighbors.h BFS.cpp BFS.h Cab.cpp Cab.h Trip.cpp Trip.h Driver.cpp Driver.h Passenger.cpp Passenger.h Listener.cpp Listener.h Notifier.cpp Notifier.h TaxiCenter.cpp TaxiCenter.h TransportationMap.cpp TransportationMap.h StandardCab.cpp StandardCab.h LuxuryCab.cpp LuxuryCab.h Client.cpp Socket.cpp Socket.h Tcp.cpp Tcp.h Udp.cpp Client.h)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.5.4.0 COMPONENTS serialization system)
add_library(core ${core_SRCS})
include_directories(${Boost_INCLUDE_DIR})

add_executable(89-210-ex3 ${SOURCE_FILES})
#target_link_libraries(89-210-ex3 gtest gtest_main)
target_link_libraries(89-210-ex3)
