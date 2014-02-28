
#include <Socket/Socket.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	sockets::InitSockets();
	struct addrinfo *result = NULL;
	struct addrinfo hints{ AI_V4MAPPED | AI_ALL, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP };

	sockets::Socket s;

	int iResult = getaddrinfo("PODOKONNIK", "2121", &hints, &result);
	if (iResult != 0) {
		return 0;
	}

	for (auto ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		s.socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (s.isInvalid()) {
			return -1;
		}

		// Connect to server.
		if (!s.connect(ptr->ai_addr, (int)ptr->ai_addrlen)) {
			s.closesocket();
			continue;
		}
		break;
	}

	if (s.isInvalid()) {
		return -1;
	}
	s.sendStr("Hello server;");
	std::cout << s.recvStr(100) << std::endl;
	system("pause");
	s.closesocket();
	sockets::ReleaseSockets();
	return 0;
}

