
#include <Socket\Socket.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	InitSockets();
	struct addrinfo *result = NULL;
	struct addrinfo hints{ 0, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP };

	Socket s;

	int iResult = getaddrinfo("localhost", "2121", &hints, &result);
	if (iResult != 0) {
		return 0;
	}

	for (auto ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		s.init(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
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
	return 0;
}

