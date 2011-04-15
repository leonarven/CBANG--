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
	sf::IPAddress addr;
} server;

struct {
	std::size_t size;
	char data[BUFFER_SIZE];
} buf;

int main (int argc, char **argv) {
    sf::SocketTCP Client;

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

    if (Client.Connect(PORT, server.addr) != sf::Socket::Done)
		return ERRNO_CANT_CONNECT;

    cout << "Yhdistetty serverille " << server.addr << endl;

	while(true) {
		if (Client.Receive(buf.data, BUFFER_SIZE, buf.size) != sf::Socket::Done)
			return ERRNO_CANT_RECEIVE;

		cout << "Vastaanotettu:\n\t" << buf.data << "\n" << endl;
	}
	cout << "Sammutetaan client" << endl;
    Client.Close();

	return 0;
}
