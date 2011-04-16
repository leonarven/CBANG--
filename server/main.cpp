#include <iostream>
#include <time.h>
#include <list>

#include <SFML/Network.hpp>

#include "../engine.hpp"
#include "../common.hpp"
#include "game.hpp"
#include "server.hpp"

void ServerLoop(unsigned short Port)
{
    // start listening to incoming connections
    if (!server.listener.Listen(Port))
        return;

    std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

    server.selector.Add(server.listener);

    // Loop while... we close the program :)
    while (true)
    {
        // Get the sockets ready for reading
        unsigned int sockets = server.selector.Wait(1);

        // We can read from each returned socket
        for (unsigned int i = 0; i < sockets; ++i)
        {
            // Get the current socket
            sf::SocketTCP Socket = server.selector.GetSocketReady(i);

            if (Socket == server.listener)
            {
                // If the listening socket is ready, it means that we can accept a new connection
                sf::IPAddress Address;
                sf::SocketTCP Client;

                server.listener.Accept(Client, &Address);
                std::cout << "Client connected ! (" << Address << ")" << std::endl;

                sf::Packet welcome;
                welcome << std::string("Welcome to BANG! server");
                Client.Send(welcome);

                // Ping failed
                if (server.ping(Client))
                    continue; // Don't accept client

                // Add player to game
                server.selector.Add(Client);
                Game.AddPlayer(Client);

            }
            else
            {
                // Else, it is a client socket so we can read the data he sent
                sf::Packet Packet;
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {

                    player* sender = Game.getPlayer(Socket);

                    std::cout << "id:" << sender->getId() << "/vuoro:" << Game.getTurnNumber() << std::endl;

                    if (sender->getId() != Game.getTurnNumber())
                        break;

                    // Extract the message and display it
                    std::string Message;
                    Packet >> Message;

                    if (Message == "skipidiskoo")
                        Game.changeTurn();
                    else if (!Message.compare("shutdown"))
                    {
                        Game.sendToAll(Packet);
                        return;
                    } else if (Message[0]=='\t') {
                        msg message = Engine.Parse((char *)Message.c_str());
                    }
                    else
                    {
                        std::cout << "From: " << sender->getId() << ": \"" << Message << "\"" << std::endl;
                        Game.sendToAll(Packet);
                    }


                }
                else
                {
                    // Error : we'd better remove the socket from the selector
                    server.selector.Remove(Socket);


                    std::cout << "Error receiving data, removing socet from selector";
                }
            }
        }
    }
}



////////////////////////////////////////////////////////////
/// Entry point of application
/// \return Application exit code
////////////////////////////////////////////////////////////
int main()
{

    srand(time(NULL));

    // Choose a random port for opening sockets (ports < 1024 are reserved)
    const unsigned short Port = PORT;
        ServerLoop(Port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
