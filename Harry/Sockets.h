#pragma once
#ifdef _WIN32
// Windows
#include <WinSock2.h>
typedef SOCKET NetSocketId;
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
typedef int NetSocketId;
#define NET_INVALID_SOCKET_ID (-1)
#define NET_SOCKET_ERROR      (-1)
#endif // _WIN32

#include <stdexcept>
#include <string>
#include <memory>

class sockError {
public:
	sockError(const std::string&  message);
};


struct socketCleaner {
	socketCleaner() {
	#ifndef _WIN32
		WSADATA info;
		if (WSAStartup(MAKEWORD(2, 0), &info))
			throw sockError("Could not start WSA");
	#endif
	}
	~socketCleaner() {
	#ifndef _WIN32
		WSACleanup();
	#endif
	}
	
};


class Socket
{
public:
	socketCleaner s;
	enum class ConnectionType { Blocking, NonBlocking };
	explicit Socket(NetSocketId sid);
	virtual ~Socket();
	void receiveBytes(void * buffer, size_t numBytes) ;
	void sendBytes(void * buffer, size_t numBytes) ;
	void Close();
protected:

	Socket();

	// platform specific.
	NetSocketId socketId;

};


using socketPtr = std::unique_ptr<Socket>;

class socketClient : public Socket {
public:
	socketClient(std::string & host, const u_short & port);
protected:

};

using socketClientPtr = std::unique_ptr<socketClient>;

class socketServer : public Socket {
public:
	socketServer(const u_short & port, int pending, Socket::ConnectionType connType);

	socketPtr acceptConnection();

};

using socketServerPtr = std::unique_ptr<socketServer>;


