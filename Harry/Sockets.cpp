#include "Sockets.h"
#include <iostream>
#ifdef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
#endif

sockError::sockError(const std::string & message) {
	#ifdef _WIN32
		std::runtime_error(message + std::string(" | sys error: ") + std::to_string(WSAGetLastError()));
	#else // !_WIN32
		std::runtime_error(message + std::string(" | sys error: ") + std::strerror(errno));
	#endif // _WIN32
}

Socket::Socket()
{
	socketId = socket(AF_INET, SOCK_STREAM, /* protocol = */ 0);
	if (socketId == NET_INVALID_SOCKET_ID)
	{
		throw sockError("Failed to create socket with 'socket(AF_INET, SOCK_STREAM, 0)'!");
	}

}

Socket::Socket(const NetSocketId sid)
	: socketId(NET_INVALID_SOCKET_ID)
{
	socketId = sid;
}

void Socket::Close()
{
	if (socketId != NET_INVALID_SOCKET_ID)
	{
		int result;

		#ifdef _WIN32
			result = closesocket(socketId);
		#else // !_WIN32
			result = close(socketId);
		#endif // _WIN32

		if (result == 0)
		{
			std::cout<<"Closed socket connection"<<std::endl;
		}
		else
		{
			std::cout<<("Failed to close a socket")<<std::endl;
		}

		socketId = NET_INVALID_SOCKET_ID;
	}
}

void Socket::receiveBytes(void	*buffer, size_t numBytes)
{
	if(socketId == NET_INVALID_SOCKET_ID)
		throw sockError("Invalid Socket ID");
	if(buffer == nullptr)
		return;
	
	long res = recv(socketId,(char *) buffer, numBytes, 0);
	
	if (res == NET_SOCKET_ERROR)
	{
		throw sockError("Failed to send! (NET_SOCKET_ERROR)");
	}
	
}

void Socket::sendBytes(void *buffer, size_t numBytes)
{
	if (socketId == NET_INVALID_SOCKET_ID)
		throw sockError("Invalid Socket ID");
	if (buffer == nullptr)
		return;
	long res = send(socketId, (char *)buffer, numBytes, 0);

	if (res == NET_SOCKET_ERROR)
	{
		throw sockError("Failed to send! (NET_SOCKET_ERROR)");
	}

}

Socket::~Socket()
{
	Close();
}


socketClient::socketClient(std::string &host, const u_short & port)
{
	if (socketId == NET_INVALID_SOCKET_ID)
		throw sockError("Invalid Socket ID");
	
	if (host.empty())
	{
		std::cout << "Host should not be empty" << std::endl;
	}
		
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

	hostent * hostEntity;
	if (isdigit(host[0])) {
		//addr.sin_addr.s_addr = inet_addr(host.c_str());
		hostEntity = gethostbyaddr((char const *)&addr, sizeof(addr), AF_INET);
	}
	else
		hostEntity = gethostbyname(host.c_str());
	if (hostEntity == nullptr)
	{
		Close();
		throw sockError("Failed to get hostent for " + host);
	}


	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = *reinterpret_cast<in_addr *>(hostEntity->h_addr);


	if (connect(socketId, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0)
	{
		Close();
		throw sockError("Failed to connect with host " + host +
			" at port #" + std::to_string(port));
	}
}

socketServer::socketServer(const u_short & port, int pending, Socket::ConnectionType connType)
{
	if (socketId == NET_INVALID_SOCKET_ID)
		throw sockError("Invalid Socket ID");

	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	if (connType == Socket::ConnectionType::NonBlocking)
	{
		#ifdef _WIN32
			u_long arg = 1;
			ioctlsocket(socketId, FIONBIO, &arg);
		#else // !_WIN32
			fcntl(socketId, F_SETFL, O_NONBLOCK);
		#endif // _WIN32
	}

	// Bind server to the port and start listening at it:
	
	if (bind(socketId, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0)
	{
		Close();
		throw sockError("Failed to 'bind()' socket to port #" +
			std::to_string(port));
	}

	if (listen(socketId, pending) != 0)
	{
		Close();
		throw sockError("Failed to 'listen()' at port #" +
			std::to_string(port));
	}

}
socketPtr socketServer::acceptConnection()
{
	if (socketId == NET_INVALID_SOCKET_ID)
		throw sockError("Invalid Socket ID");
	errno = 0;
	const NetSocketId newSocket = accept(socketId, nullptr, nullptr);
	if (newSocket == NET_INVALID_SOCKET_ID)
	{
		// Non-blocking call / no request pending
		#ifdef _WIN32
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				return nullptr;
			}
		#else // !_WIN32
			if (errno == EAGAIN)
			{
				return nullptr;
			}
		#endif // _WIN32

		throw sockError("'accept()' failed with an invalid socketId!");
	}

	return socketPtr(new Socket(newSocket));

}
