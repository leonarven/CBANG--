#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>

class _server {
public:
    ~_server()
    {
        listener.Close();
    }

    bool ping(sf::SocketTCP socket)
    {
        sf::Packet packet;
        std::string ping = "P" + to_string(rand());

		std::cout << "  <<< " << ping 	<< std::endl;

        packet << ping;
        socket.Send(packet);
        packet.Clear();
        socket.Receive(packet);

        std::string result;
        packet >> result;

		std::cout << "  >>> " << result << std::endl;

        return result.compare(ping);
    }




    sf::SelectorTCP selector;
    sf::SocketTCP listener;
} server;

#endif // SERVER_HPP_INCLUDED
