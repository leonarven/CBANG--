#include <SFML/Network.hpp>
#include <iostream>

void DoServerTCP(unsigned short Port) // short
{
    // Create a TCP socket for communicating with clients
    sf::SocketTCP Server;

    // Listen to a port for incoming connections
    if (!Server.Listen(Port))
        return;
	{
    std::cout << "Server is listening to port " << Port << ", waiting for connections... " << std::endl;
	}


    // Wait for a connection
    sf::IPAddress ClientAddress;
    sf::SocketTCP Client;
    Server.Accept(Client, &ClientAddress);
    std::cout << "Client connected : " << ClientAddress << std::endl;

    // Send a message to the client
    char ToSend[128] = "Hi, I'm the server";
    if (Client.Send(ToSend, sizeof(ToSend)) != sf::Socket::Done)
        return;
	{
    std::cout << "Message sent to the client : \"" << ToSend << "\"" << std::endl;
	}

    // Receive a message back from the client
    char Message[128]; //128
    std::size_t Received;
    if (Client.Receive(Message, sizeof(Message), Received) != sf::Socket::Done)
        return;
	{
    // Show the message
    std::cout << "Message received from the client : \"" << Message << "\"" << std::endl;
	}

    // Close the sockets when we're done
    Client.Close();
    Server.Close();
}


int main()
{
	using namespace std;

	cout << "Identifying PC ...\n" << endl;

	sf::IPAddress Address1 = sf::IPAddress::GetLocalAddress();
	sf::IPAddress Address2 = sf::IPAddress::GetPublicAddress();

	cout << "Local  IP:" << Address1 << endl;
	cout << "Public IP:" << Address2 << endl << endl;
	cout << "Identification stage 1 complete ...\n";

	int x=4567;
	DoServerTCP(x);

	int a;
	cin >> a;
	return 0;
}
