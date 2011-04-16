#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../common.hpp"
#include "../engine.hpp"

using namespace std;

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
sf::Packet packetSend, packetReceive;

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
	string str;
	server.socket.Receive(packetReceive);
	packetReceive >> str;
	packetSend << str;
	cout << "< \"" <<  str<< "\"" << endl;
	bool Connected = (server.socket.Send(packetSend) == sf::Socket::Done);
	packetReceive.Clear();
	server.socket.Receive(packetReceive);
	string tmp;
	packetReceive >> tmp;
	cout << "< \"" << tmp << "\"" << endl;

	while (Connected) {
		packetSend.Clear();
		cout << "> ";
        std::getline(std::cin, str);
        packetSend << str;
        Connected = (server.socket.Send(packetSend) == sf::Socket::Done && str.compare("shutdown"));

		packetReceive.Clear();
        server.socket.Receive(packetReceive);
        string tmp;
        packetReceive >> tmp;
        cout << "< \"" << tmp << "\"" << endl;
	}
	cout << "Sammutetaan client" << endl;
    server.socket.Close();

	return 0;
}
