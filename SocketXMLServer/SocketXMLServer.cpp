
#include <Socket/Socket.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "starts..." << std::endl;
	InitSockets();
	struct addrinfo *result = NULL;
	struct addrinfo hints{ AI_PASSIVE, AF_INET, SOCK_STREAM, IPPROTO_TCP };
	
	Socket s;

	int iResult = getaddrinfo(NULL, "2121", &hints, &result);
	if (iResult != 0) {
		return 0;
	}

	s.init(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (s.isInvalid()) {
		return -1;
	}
	s.bind(result->ai_addr, (int)result->ai_addrlen);
	if (s.isInvalid()) {
		return -1;
	}
	s.listen();
	if (s.isInvalid()) {
		return -1;
	}
	freeaddrinfo(result);

	Socket client = s.accept(nullptr, nullptr);
	s.closesocket();
	
	std::cout << client.recvStr(100) << std::endl;
	client.sendStr("Hello bro;");
	system("pause");
	return 0;
}

