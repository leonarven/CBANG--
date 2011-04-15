
// SDL_net Server | r3dux.org | 14/01/2011

#include <iostream>
#include <cstdlib>
#include <string>

#include "game.hpp"

const unsigned short PORT        = 6665;            // The port our server will listen for incoming connecions on
const unsigned short BUFFER_SIZE = 512;             // Size of our message buffer
const unsigned short MAX_SOCKETS = 4;               // Max number of sockets
const unsigned short MAX_CLIENTS = MAX_SOCKETS - 1; // Max number of clients in our socket set (-1 because we place thee server's listening socket as the first socket in the set)
using namespace std;

// Messages to send back to any connecting client to let them know if we can accept the connection or not
const string SERVER_NOT_FULL = "OK";
const string SERVER_FULL     = "FULL";

int main(int argc, char **argv)
{


    return 0;
}
