//
// game.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Miro Nieminen (leonarven@gmail.com) ja sante ^^
//

//PROTOCOL:
//sender
//destination
//data = string

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Network.hpp>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

/*
Kommunikaatio:
1. yhteys muodostetaan serveriin
2. serveri lähettää tervetuloa viestin
3. serveri lähettää pingin joka lähetetään sellaisenaan takaisin
4. serveri lähettää vuoronumeron
5. kun pelaajia on tarpeeksi serveri kertoo vuoron siirtymisen pelaajalle 1.


6.  Pelaaja lähettää serverille käskyjä
    Serveri vastaa (aina). tarvittaessa viesti lähetetään kaikille pelaajille
    ...
    Pelaaja lähettää vuoronvaihdon
    Serveri vastaa

7. Serveri kertoo kaikille pelaajille
    -> 6
*/

class _Engine
{
public:
	msg Parse(std::string buf)
	{
		msg message;
		message.buf = (char *)buf.c_str();
		message.type = (MSG_TYPE)buf[0];

		message.sender = buf[1] - 48;
		message.target = buf[2] - 48;

		if (buf.length() >= 3)
			message.data = buf.substr(3);

        return message;
    }

/*
	std::string sImplode(MSG_TYPE, unsigned sender, unsigned target, std::string data)
	{

    }
	sf::Packet sImplode(MSG_TYPE, unsigned sender, unsigned target, std::string data)
	{

    }*/




} Engine;

#endif // GAME_HPP

