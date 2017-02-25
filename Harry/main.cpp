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
	std::cout << "Enter your username\n";
	std::string name;
	std::cin >> name;

	std::cout << "Enter your character choice 0-6\n";
	int playerChoice;
	std::cin >> playerChoice;

	

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
		/*socketClient client(ip, SOCK_PORT, 2048);
		char input[1000];
		client.receiveBytes(input);
		std::cout << input;	//connected msg
		
		//client.sendBytes((name + std::to_string(playerChoice)).c_str());

		client.receiveBytes(input); */

		//process input to find noOfPlayers,indexOfClient, Player data

		int noOfPlayers = 3;
		int indexOfClient = 0;
		std::vector<Player> players;
		players.emplace_back(name, glm::vec2(30.0f, 30.0f), playerChoice);
		players.emplace_back("Sid", glm::vec2(50.0f, 50.0f), 0);
		players.emplace_back("Sid2", glm::vec2(60.0f, 30.0f), 4);
		SimpleGame mainGame(noOfPlayers,indexOfClient,players);
		mainGame.run();
	}	
	if(choice==1)
		sockThread.join();
	return 0;
}