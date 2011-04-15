#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "../common.hpp"


using namespace std;
    //Client.Close();

class {
	public:
	sf::IPAddress addr;
} server;

int main (int argc, char **argv) {
 	if (argc<2) {
		cout << "Le Phuil!" << endl;
		return 0;
	} else {
		server.addr = sf::IPAddress(argv[1]);
		if (!server.addr.IsValid()) {
			cout << "Osoite ei ole kelvollinen." << endl;
			return 0;
		}
	}
	return 1;

/*    // Create a TCP socket for communicating with server
    sf::SocketTCP Client;

    // Connect to the specified server
    if (Client.Connect(PORT, ServerAddress) != sf::Socket::Done)
        return;
	{
    std::cout << "Connected to server " << ServerAddress << std::endl;
	}

    // Receive a message from the client
    char Message[128];
    std::size_t Received;
    if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
        return;

    // Show it
	{
    std::cout << "Message received from server : \"" << Message << "\"" << std::endl;
	}

    // Define a message to send back to the server
    char ToSend[128] = "Hi, I'm a client !";

    // Send the message
    if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done)
        return;
	{
    std::cout << "MEssage sent to server : \"" << ToSend << "\"" << std::endl;
	}

	int a;
	std::cin >> a;
	return 0;*/
}
