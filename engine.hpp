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
#include "../common.hpp"

class
{
public:
    msg Parse(char* buf)
    {
        msg message;
        message.buf = buf;

        if (buf[0] == '\t' || buf[0] == '/') // Buffer is command
        {
            switch (buf[1])
            {
            case 'A':
                message.type = ACTION;
                break;
            default:
                message.type = TEXT;
                break;
            }

            for (unsigned int i = 2; i < strlen(buf); i++)
            {
                message.options.push_back(buf[i] - '0');
                std::cout << message.options.back() << std::endl;
            }
        }
        else
            message.type = TEXT;


        return message;
    }




} Game;

#endif // GAME_HPP
