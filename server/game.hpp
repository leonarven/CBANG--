#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <map>

#include "server.hpp"

#include "../player.hpp"
#include "../common.hpp"

class _game
{
public:
    ~_game()
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++)
            delete ite->second;
    }

    void AddPlayer(sf::SocketTCP _socket)
    {
        players[_socket] = new player(_socket, players.size() + 1 ,0, 0, 4);

        sf::Packet packet;
        tmp = std::string("T0" + to_string(players.size()));

        packet << tmp;
        _socket.Send(packet);

        if (players.size() == minPlayersInGame)
        {
            this->turn = 1;
            sendToAll("M09Peli alkaa!");
            sendToAll("T01");
        }

        //TODO: mitä pitää kertoo muista pelaajista
    }

    player* getPlayer(sf::SocketTCP _socket) { return players[_socket]; }

    void deletePlayer(sf::SocketTCP _socket)
    {
        delete players[_socket];
        players.erase(_socket);

        DEBUG("POISTETTIIN PELAAJA, odotettavissa häikkää vuorosysteemissä")

        if (players.size() < minPlayersInGame)
            setTurn(0);
    }

    int playersCount()
    {
        return this->players.size();
    }

    void setTurn(int _turn)
    {
        this->turn = turn;
        sendToAll("T0" + to_string(turn));
    }

    void changeTurn()
    {
        if (++turn > players.size())
            turn = 1;

        sendToAll(std::string("T0") + to_string(turn));
    }

    unsigned getTurnNumber() { return turn; }

    void sendToAll(const std::string& string)
    {
        sf::Packet packet;
        packet << string;
        sendToAll(packet);
		std::cout << "A <<< " << string << std::endl;
    }
    void sendToAll(sf::Packet packet)
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
            ite->second->getSocket().Send(packet);
        }
    }


    void sendToAllExceptOne(unsigned id, const std::string& message)
    {
        sf::Packet packet;
        packet << message;

        sendToAllExceptOne(id, packet);
    }

    void sendToAllExceptOne(unsigned id, sf::Packet message)
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
           if (ite->second->getId() == id) {
                continue;
            }
            ite->second->getSocket().Send(message);
        }
    }




    void pingToAllExceptTheChosenONEWhoIsOnHERPromissedTURN()
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
            if (ite->second->getId() == turn)
                continue;

            if (server.ping(ite->second->getSocket()))
            {
                std::cout << "  --- EI vASTATA MUN PINGGIIIIN PRKLLL!! >: " << std::endl;
                exit(135);
            }
        }
    }



private:
    std::map<sf::SocketTCP, player*> players;

	std::string tmp;
    unsigned turn;

} Game;

#endif // GAME_HPP_INCLUDED
