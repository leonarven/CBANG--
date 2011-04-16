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

#include <vector>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

class _Engine
{
public:
	msg Parse(std::string buf) { return this->Parse((char*)buf.c_str()); }
	msg Parse(char* buf)
	{
		msg message;
		message.buf = buf;
		message.type = (MSG_TYPE)buf[0];

		DEBUG((int)buf[1])
		DEBUG((int)buf[2])

		message.sender = buf[1] - 48;
		message.target = buf[2] - 48;

		DEBUG(buf)
		DEBUG(strlen(buf))

		if (strlen(buf) <= 3)
			message.data = std::string(buf).substr(3);


        return message;
    }




} Engine;

#endif // GAME_HPP

