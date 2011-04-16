#include<iostream>

#include<SFML/Network.hpp>

#include "../engine.hpp"
#include "../common.hpp"
#include "game.hpp"

class {
public:
    sf::SelectorTCP selector;
    sf::SocketTCP listener;

} server;

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
        unsigned int sockets = server.selector.Wait();

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

                // Add it to the selector
                server.selector.Add(Client);

                sf::Packet welcome;
                welcome << std::string("Welcome to BANG! server");
                Client.Send(welcome);
            }
            else
            {
                // Else, it is a client socket so we can read the data he sent
                sf::Packet Packet;
                if (Socket.Receive(Packet) == sf::Socket::Done)
                {
                    // Extract the message and display it
                    std::string Message;
                    Packet >> Message;

                    std::cout << "A client says : \"" << Message << "\"" << std::endl;

                    msg message = Engine.Parse((char *)Message.c_str());

                    if (Socket.Send(Packet) != sf::Socket::Done)
                    {
                        std::cout << "Couldn't send data to client" << std::endl;
                        server.selector.Remove(Socket);
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



    // Choose a random port for opening sockets (ports < 1024 are reserved)
    const unsigned short Port = PORT;
        ServerLoop(Port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
