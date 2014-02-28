
#include <Socket/ClientTCPIP.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	sockets::InitSockets();
	
	sockets::ClientTCPIP s("podokonnik",2121, sockets::SockType::TCPIPv4v6, 1212);

	s.sendStr("Hello server;");
	std::cout << std::endl << "Sending to " << s.peerIp() << ':' << s.peerPort() << " Hello server;";
	std::cout << std::endl << "Receviving from " << s.ip() << ':' << s.port() << ' ' <<s.recvStr(100) << std::endl;

	system("pause");
	s.closesocket();
	
	sockets::ReleaseSockets();
	return 0;
}

