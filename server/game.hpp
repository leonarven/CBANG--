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


        if (players.size() >= minPlayersInGame)
        {
            changeTurn();

            packet.Clear();
            packet << "\tT1";
            sendToAll(packet);
            packet.Clear();
            packet << "Peli alkaa!";
            sendToAll(packet);
        }

        //TODO: mitä pitää kertoo muista pelaajista
    }

    player* getPlayer(sf::SocketTCP _socket)
    {
        return players[_socket];
    }

    //void changeTurn(int _turn) { this->turn = 1 + (_turn % players.size()); }
    void changeTurn()
    {
        if (++turn > players.size())
            turn = 1;

        sf::Packet newTurn;
        newTurn << "\tT" + to_string(turn);
        sendToAll(newTurn);
    }

    int getTurnNumber() { return turn; }

    void sendToAll(const std::string& string)
    {
        sf::Packet packet;
        packet << string;
        sendToAll(packet);
    }
    void sendToAll(sf::Packet packet)
    {
        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
            ite->second->getSocket().Send(packet);
        }
    }

    void pingToAllExceptTheChosenONEWhoIsOnHERPromissedTURN()
    {
        std::string ping("\tP" + to_string(rand()));
        std::string responce;
        sf::Packet pingPacket, pingResponce;
        pingPacket << ping;

        std::map<sf::SocketTCP, player*>::iterator ite;
        for (ite = players.begin(); ite != players.end(); ite++) {
            if (ite->second->getId() == turn)
                continue;

            ite->second->getSocket().Send(pingPacket);
            ite->second->getSocket().Receive(pingResponce);
            pingResponce >> responce;

            if (responce.compare(ping))
            {
                std::cout << "EI vASTATA MUN PINGGIIIIN!! >: " << std::endl;
                int NYT_SUUTUIN = 256;
                exit(NYT_SUUTUIN);
            }
        }
    }



private:
    std::map<sf::SocketTCP, player*> players;

    unsigned turn;

} Game;

#endif // GAME_HPP_INCLUDED
