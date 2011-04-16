//
// game.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Miro Nieminen (leonarven@gmail.com) ja sante ^^
//

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

		for (unsigned int i = 1; i < strlen(buf); i++)
		{
			message.options.push_back(buf[i]);
		}
        return message;
    }




} Engine;

#endif // GAME_HPP

