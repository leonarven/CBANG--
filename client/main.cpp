#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../common.hpp"

using namespace std;

enum {
	ERRNO_TOO_LESS_ARGS,
	ERRNO_NOT_VALID_ADDR,
	ERRNO_CANT_CONNECT,
	ERRNO_CANT_RECEIVE,
	ERRNO_CANT_SEND
};

class {
	public:
    sf::SocketTCP socket;
	sf::IPAddress addr;
} server;

struct {
	std::size_t size;
	char data[BUFFER_SIZE];
} buf;

string str;

int main (int argc, char **argv) {
 	if (argc<2) {
		cout << "Käyttö: client <<Serverin osoite>>!" << endl;
		return ERRNO_TOO_LESS_ARGS;
	} else {
		server.addr = sf::IPAddress(argv[1]);
		if (!server.addr.IsValid()) {
			cout << "Osoite ei ole kelvollinen." << endl;
			return ERRNO_NOT_VALID_ADDR;
		}
	}

    if (server.socket.Connect(PORT, server.addr) != sf::Socket::Done)
		return ERRNO_CANT_CONNECT;

    cout << "Yhdistetty serverille " << server.addr << endl;

	bool Connected = true;
	while (Connected) {
        sf::Packet Packet;
        std::getline(std::cin, str);
        Packet << str;
        Connected = (server.socket.Send(Packet) == sf::Socket::Done && str.compare("shutdown"));
	}
	cout << "Sammutetaan client" << endl;
    server.socket.Close();

	return 0;
}
