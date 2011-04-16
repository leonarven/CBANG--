#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../common.hpp"
#include "../engine.hpp"
#include "../player.hpp"

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

sf::Packet packetSend, packetReceive;

vector<player> players;
int turn = 1, myId = 0;

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
	string str;
	/* PING */
	server.socket.Receive(packetReceive);
	packetReceive >> str;
	cout << "< \"" <<  str<< "\"" << endl;
	packetSend << str;
	cout << "> \"" <<  str<< "\"" << endl;
	bool Connected = (server.socket.Send(packetSend) == sf::Socket::Done);
	/* /PING */

	msg tmp;

	server.socket.Receive(packetReceive);
	packetReceive >> str;
	tmp = Engine.Parse(str);
	myId = tmp.options.at(0)-(int)'0';
	cout << myId << ": < \"" << str << "\"" << endl;

	while (Connected) {
		if (turn == myId) {
			cout << myId << ": > ";
			packetSend.Clear();
			std::getline(std::cin, str);
			packetSend << str;
			Connected = (server.socket.Send(packetSend) == sf::Socket::Done && str.compare("shutdown"));
		}
        server.socket.Receive(packetReceive);
        packetReceive >> str;
        Engine.Parse(str);
        cout << myId << ": < \"" << str<< "\"" << endl;
	}
	cout << "Sammutetaan client" << endl;
    server.socket.Close();

	return 0;
}
