
#include <Socket/ServerTCPIP.hpp>
#include <iostream>

using namespace sockets;

#include <mutex>

struct client {
	
	bool operator() (Socket& sock) {
		static std::mutex m;
		std::lock_guard<std::mutex> lck(m);
		std::cout << std::endl << "Come to " << sock.ip() << " on port " << sock.port() << " : " << sock.recvStr(50) << ".";
		std::cout << std::endl << "Sending to " << sock.peerIp() << " client on port " << sock.peerPort() << " : " << "Hello bro!" << "." << std::endl;
		sock.sendStr("Hello bro!");
		return true;
	}
};

auto proc = [](Socket& sock){return true; };

int main(int argc, char* argv[])
{
	std::cout << "starts..." << std::endl;
	InitSockets();
	
	SocketServerTCPIP serv(sockets::SockType::TCPIPv6, proc, client(), proc, 2121);

	system("pause");
	ReleaseSockets();
	return 0;
}

