
#include <Socket/ServerTCPIPv4.hpp>
#include <iostream>

using namespace sockets;

#include <mutex>

struct client {
	
	void operator() (Socket& sock) {
		static std::mutex m;
		std::unique_lock<std::mutex> lck(m);
		std::cout << std::endl << "Come from client  " << SOCKET(sock) << " : " << sock.recvStr(50) << "." << std::endl;
		std::cout << "Sending to client " << SOCKET(sock) << " : " << "Hello bro!" << "." << std::endl;
		sock.sendStr("Hello bro!");
	}
};

int main(int argc, char* argv[])
{
	std::cout << "starts..." << std::endl;
	InitSockets();
	
	SocketServerTCPIPv4 serv(client(), 2121);

	system("pause");
	ReleaseSockets();
	return 0;
}

