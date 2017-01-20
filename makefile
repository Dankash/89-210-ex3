all:
	g++  *.cpp sockets/*.h sockets/*.cpp *.h -pthread -D _DISABLE_INFO_LOGS -D _DISABLE_STATUS -DBOOST_LOG_DYN_LINK -lboost_serialization -I -lm -ansi -pedantic -std=c++0x -o Server.out

	g++   -pthread -D _DISABLE_INFO_LOGS -D _DISABLE_STATUS -DBOOST_LOG_DYN_LINK -lboost_serialization -I -lm -ansi -pedantic -std=c++0x -o Client.out
	 
