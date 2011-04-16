#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>

class {
public:
    bool ping(sf::SocketTCP socket)
    {
        sf::Packet packet;
        std::string ping = "\tT" + to_string(rand());

        socket.Send(packet);
        packet.Clear();
        socket.Receive(packet);

        std::string result;
        packet >> result;
        return !result.compare(ping);
    }


    sf::SelectorTCP selector;
    sf::SocketTCP listener;
} server;

#endif // SERVER_HPP_INCLUDED
