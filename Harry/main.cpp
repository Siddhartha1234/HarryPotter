#include <GL/glew.h>
#include "SimpleGame.h"
#include <iostream>
#include "Sockets.h"
#include <thread>
#include <vector>
#include "player.h"
//#include "MainGame.h"

int main(int argc, char** argv)
{
	int choice;
	std::cout << "Enter 1 to be server,2 to be client\n";
	std::cin >> choice;
	std::string SOCK_PORT = "100";
	std::thread sockThread;

	WSADATA info;
	if (WSAStartup(MAKEWORD(2, 0), &info))
		throw sockError("Could not start WSA");

	if (choice == 1)
	{
		int clients;
		std::cout << "Enter number of Clients" << std::endl;
		std::cin >> clients;
		socketServer server(SOCK_PORT,clients, Socket::ConnectionType::NonBlocking,2048);
		sockThread =  std::thread(&socketServer::select_activity, server);
	}
	else if (choice == 2)
	{
		std::cout << "Enter server's IP address\n";
		std::string ip;
		std::cin >> ip;
		socketClient client(ip, SOCK_PORT, 2048);
		char input[1000];
		client.receiveBytes(input);
		std::cout << input;
		client.receiveBytes(input);
		int noOfPlayers = 5;
		int indexOfClient = 1;
		std::vector<Player> players;
		SimpleGame mainGame(noOfPlayers,indexOfClient,players);
		mainGame.run();
	}	
	sockThread.join();
	return 0;
}