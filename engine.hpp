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

        // if buffer is command
        if (buf[0] == '\t' || buf[0] == '/')
        {
            switch (buf[1])
            {
            case 'A':
                message.type = ACTION;
                break;
            case 'T':
                break;
            case 'C':
                break;
            case 'P':
                break;
            case 'D':
                break;
            default:
                message.type = TEXT;
                return message;
            }

            for (unsigned int i = 2; i < strlen(buf); i++)
            {
                message.options.push_back((int)buf[i]);
            }
        }
        else
            message.type = TEXT;

        return message;
    }




} Engine;

#endif // GAME_HPP

