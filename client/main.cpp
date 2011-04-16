#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../common.hpp"
#include "../engine.hpp"
#include "../player.hpp"

using namespace std;

class _server {
	public:
    sf::SocketTCP socket;
	sf::IPAddress addr;
} server;

struct _buf {
	std::size_t size;
	char data[BUFFER_SIZE];
} buf;

sf::Packet packetSend, packetReceive;

vector<player> players;
int turn = 0, myId = 0;

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
	server.socket.Receive(packetReceive);
	packetReceive >> str;
	cout << "< \"" <<  str<< "\"" << endl;
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
		DEBUG("")
		packetSend.Clear();
		packetReceive.Clear();
		if (turn == myId) {
			cout << myId << ": > ";
			std::getline(std::cin, str);
		DEBUG(str)
			packetSend << str;
			if (!str.compare("shutdown")) {
				str = string("S");
				Connected = false;
		DEBUG(str)
			} else {
				Connected = (server.socket.Send(packetSend) == sf::Socket::Done);
		DEBUG(str)
			}
		}

        server.socket.Receive(packetReceive);
        packetReceive >> str;
        tmp = Engine.Parse(str);
		DEBUG(str)

		DEBUG(tmp.type)
		DEBUG(tmp.options)
        cout << myId << ": < \"" << str<< "\"" << endl;
		switch(tmp.type) {
			case SHUTDOWN:
				Connected = false;
				break;
			case TURN:
				turn = atoi(tmp.options.c_str());
				DEBUG(string("Vuoro vaihtui; " + turn));
				break;
			case PING:
				packetSend.Clear();
				packetSend << str;
				server.socket.Send(packetSend);
				packetSend.Clear();
				break;
		}
		DEBUG(str)
	}
	cout << "Sammutetaan client" << endl;
    server.socket.Close();

	return 0;
}
