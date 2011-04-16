#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "common.hpp"
#include "card.hpp"

#include <SFML/Network.hpp>

class player
{
    public:
    player(sf::SocketTCP _socket, int id_, int _role, int _character, int _mHealth) :
        socket(_socket), id(id_), role(_role), character(_character), mHealth(_mHealth), health(_mHealth)
    {
        for (int i = 0; i < _mHealth; i++)
        {
            //TODO: arvo kortit tässä
        }
    }

    sf::SocketTCP getSocket()   { return this->socket; }
    unsigned getId()             { return this->id; }
    int		getHealt()		    { return this->health; }
    int		getMHealt()		    { return this->mHealth; }
    int		getRole()		    { return this->role; }
    int		getCharacter()	    { return this->character; }
    void	getCard(CARDS _card, bool table = false) {
        if (table) {
            this->table.push_back(card(_card));
            this->cards.push_back(&this->table.back());
        } else {
            this->hand.push_back(card(_card));
            this->cards.push_back(&this->hand.back());
        }
    }
    void setHealth(int nHealth) { this->health = nHealth; }



private:

    sf::SocketTCP socket;
    unsigned id;

    std::vector<card>	table;
    std::vector<card>	hand;
    std::vector<card*>	cards;
    const int role, character, mHealth;
    int health;
};

#endif // PLAYER_HPP_INCLUDED
