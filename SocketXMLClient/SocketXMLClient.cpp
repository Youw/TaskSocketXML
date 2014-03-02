
#include <Socket/ClientTCPIP.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	sockets::InitSockets();
	
	if (argc<2) {
		std::cout<< "Usage: " << argv[0] << " <server address>" << std::endl;
		return 0;
	}
	sockets::ClientTCPIP s(argv[1],2121, sockets::SockType::TCPIPv4v6);
	if (s.isInvalid()) {
		std::cout<< "Can not create socket..." << std::endl;
		return 0;
	}
	std::cout << std::endl << "Sending to " << s.peerIp() << ':' << s.peerPort() << " Hello server;";
	s.sendStr("Hello server;");
	std::cout << std::endl << "Receviving from " << s.ip() << ':' << s.port() << ' ' <<s.recvStr(100) << std::endl;

	std::cout<< "Press enter to exit...\n" << std::endl;
	std::cin.get();
	s.closesocket();
	
	sockets::ReleaseSockets();
	return 0;
}

