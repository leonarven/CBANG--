#include<iostream>

#include<SFML/Network.hpp>

#include "../common.hpp"


void ServerLoop(unsigned short Port)
{
    // Create a socket for listening to incoming connections
    sf::SocketTCP listener;
    if (!listener.Listen(Port))
        return;

    std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

    // Create a selector for handling several sockets (the listener + the socket associated to each client)
    sf::SelectorTCP Selector;

    // Add the listener
    Selector.Add(listener);

    // Loop while... we close the program :)
    while (true)
    {
        // Get the sockets ready for reading
        unsigned int NbSockets = Selector.Wait();

        // We can read from each returned socket
        for (unsigned int i = 0; i < NbSockets; ++i)
        {
            // Get the current socket
            sf::SocketTCP Socket = Selector.GetSocketReady(i);

            if (Socket == listener)
            {
                // If the listening socket is ready, it means that we can accept a new connection
                sf::IPAddress Address;
                sf::SocketTCP Client;
                listener.Accept(Client, &Address);
                std::cout << "Client connected ! (" << Address << ")" << std::endl;

                // Add it to the selector
                Selector.Add(Client);

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
                    Packet.Clear();
                    std::cout << "A client says : \"" << Message << "\"" << std::endl;



                    Packet << Message;

                    std::cout << "lähetetään: " << Message << std::endl;

                    if (Socket.Send(Packet) != sf::Socket::Done)
                        std::cout << "error sending" << std::endl;;
                }
                else
                {
                    // Error : we'd better remove the socket from the selector
                    Selector.Remove(Socket);
                }
            }
        }
    }
}


#include "game.hpp"

////////////////////////////////////////////////////////////
/// Entry point of application
/// \return Application exit code
////////////////////////////////////////////////////////////
int main()
{
    msg message = Game.Parse("\tA345");



    // Choose a random port for opening sockets (ports < 1024 are reserved)
    const unsigned short Port = PORT;
        ServerLoop(Port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
