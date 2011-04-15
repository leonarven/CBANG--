#include<iostream>
#include<SFML/Network.hpp>
#include "../common.hpp"


void DoServer(unsigned short Port)
{
    // Create a socket for listening to incoming connections
    sf::SocketTCP Listener;
    if (!Listener.Listen(Port))
        return;
    std::cout << "Listening to port " << Port << ", waiting for connections..." << std::endl;

    // Create a selector for handling several sockets (the listener + the socket associated to each client)
    sf::SelectorTCP Selector;

    // Add the listener
    Selector.Add(Listener);

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

            if (Socket == Listener)
            {
                // If the listening socket is ready, it means that we can accept a new connection
                sf::IPAddress Address;
                sf::SocketTCP Client;
                Listener.Accept(Client, &Address);
                std::cout << "Client connected ! (" << Address << ")" << std::endl;

                // Add it to the selector
                Selector.Add(Client);
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


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Choose a random port for opening sockets (ports < 1024 are reserved)
    const unsigned short Port = PORT;
        DoServer(Port);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
