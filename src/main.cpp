#include "../include/network/Server.hpp"

int main(int ac, char **av)
{
    try
    {
        if (ac != 3)
		    throw std::runtime_error("Usage: ./ircserv <port> <password>");

        Server server(av[1], av[2]);
        server.makeSock();
        server.loop();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
