main: server.cpp client.cpp
	g++ -std=c++11 -o server server.cpp -lpthread -I.
	g++ -std=c++11 -o client client.cpp -lpthread -I.