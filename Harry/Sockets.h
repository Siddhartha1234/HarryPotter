#pragma once
#ifdef _WIN32
// Windows
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET NetSocketId;
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define NET_INVALID_SOCKET_ID INVALID_SOCKET
#define NET_SOCKET_ERROR      SOCKET_ERROR
#else // !_WIN32
//Unix
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif // _WIN32

#include <stdexcept>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
class sockError {
public:
	sockError(const std::string&  message);
};



class Socket
{
public:
	enum class ConnectionType { Blocking, NonBlocking };
	~Socket();
	
protected:
	size_t MAX_BUFFER_SIZE;
	fd_set readfds;
	Socket();
	Socket(size_t MAX_BUFFER_SIZE);

};

class socketClient : public Socket {
public:
	socketClient(std::string & host, std::string & port, size_t max_size);
	void sendBytes(void * buffer);
	void receiveBytes(void *receiveBuffer);
private:
	std::string host;
	u_short port;
	SOCKET ConnectSocket;
};


class socketServer : public Socket {
public:
	socketServer(std::string  & port,int MAX_CONN,Socket::ConnectionType connType);
	void select_activity();
	void socketServer::sendBytes(SOCKET &newSocket, void *buffer);
private :
	SOCKET master;
	SOCKET * clients;
	int max_clients;
	struct sockaddr_in server, address;
	char * buffer;
	std::vector<std::string> collectedData;
	std::vector<bool> flag;
};



