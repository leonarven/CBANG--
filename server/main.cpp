#include <iostream>
#include <time.h>
#include <string.h>

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

    std::cout << "  --- Listening to port " << Port << ", waiting for connections..." << std::endl;

    server.selector.Add(server.listener);

    // Loop while... we close the program :)
    while (true)
    {
        // Get the sockets ready for reading
        unsigned int sockets = server.selector.Wait(1);

        // We can read from each returned socket
        for (unsigned int i = 0; i < sockets; ++i)
        {
            // Get the current socke

            sf::SocketTCP Socket = server.selector.GetSocketReady(i);

            if (Socket == server.listener)
            {
                // If the listening socket is ready, it means that we can accept a new connection
                sf::IPAddress Address;
                sf::SocketTCP Client;

                server.listener.Accept(Client, &Address);

                sf::Packet welcome;
                welcome << std::string("M09Welcome to BANG! server");
                Client.Send(welcome);

				std::cout << "  --- Client connected ! (" << Address << ")" << std::endl;

                // Ping failed
				if (server.ping(Client)){
                    std::cout << "   --> Ping failed" << std::endl;
                    continue; // Don't accept client
                }
                // Add player to game
                server.selector.Add(Client);
                Game.AddPlayer(Client);

            }
            else
            {
                sf::Packet Packet;

                // Else, it is a client socket so we can read the data he sent
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {

                    player* sender = Game.getPlayer(Socket);

                    if (sender->getId() != Game.getTurnNumber()){
						break;
                    }

                    std::string Message;
                    Packet >> Message;
                    Packet.Clear();

                    std::cout << sender->getId() << " >>> " << Message << std::endl;

                    if (Message.length() < 3) {
                        std::cout << "    > " << "Invalid packet" << std::endl;

                        Message = "M0" + to_string(sender->getId()) + "Invalid packet";
                        Packet << Message;

                        //Return to sender
                        sender->getSocket().Send(Packet);

                        continue;
                    }

                    Message.replace(1, 1, to_string(sender->getId()));

                    msg message = Engine.Parse((char *)Message.c_str());

                    switch (message.type)
                    {
                    case ACTION:

                        break;

                    case DIE:
                    	return; //FIXME
                        break;

                    case TEXT:
                        Game.sendToAll(Message);
                        break;

                    case ENDTURN:
                        Game.changeTurn();
                        break;

                    case SHUTDOWN:
                        return;

                    default:
                        std::cout << "    > Unknown message type" << std::endl;
                        Packet << "M0" + to_string(sender->getId()) + "Unknown message type";
                        sender->getSocket().Send(Packet);
                        break;
                    }

                }
                else
                {
                    // Error : we'd better remove the socket from the selector
                    server.selector.Remove(Socket);
                    Game.deletePlayer(Socket);

                    //TODO: tässä kohtaa client jostain syystä lähti pelistä. tee jotain...


                    std::cout << "  --- Error receiving data, removing socet from selector" << std::endl;
                }
            }
        }
    }
}



////////////////////////////////////////////////////////////
/// Entry point of application
/// \return Application exit code
////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc == 2) minPlayersInGame = atoi(argv[1]);

    srand(time(NULL));

    // Choose a random port for opening sockets (ports < 1024 are reserved)
    const unsigned short Port = PORT;
        ServerLoop(Port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
