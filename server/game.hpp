#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <map>

#include "../player.hpp"
#include "../common.hpp"

class
{
public:
    void AddPlayer(sf::SocketTCP _socket)
    {
        //TODO: vapauta muistia...
        players[_socket] = new player(_socket, players.size() + 1 ,0, 0, 4);

        sf::Packet packet;
        packet << std::string("\tT" + to_string(players.size()));
        _socket.Send(packet);



        //TODO: mitä pitää kertoo muista pelaajista
    }

    void resetGame()
    {
        turn = 1;
    }

    player* getPlayer(sf::SocketTCP _socket)
    {
        return players[_socket];
    }

    void changeTurn()
    {
        if (++turn > players.size())
            turn = 1;

    }

    int getTurnNumber() { return turn; }

    void sendToAll(sf::Packet packet)
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
            ite->second->getSocket().Send(packet);
        }
    }


private:
    std::map<sf::SocketTCP, player*> players;

    unsigned turn;

} Game;

#endif // GAME_HPP_INCLUDED
