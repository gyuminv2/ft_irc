#include "../../include/command/Command.hpp"
#include <stdio.h>

void Command::Quit()
{
	std::string print = ":127.0.0.1 ERROR :Bye for now!\r\n";
    send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0);

    print = ":" + _caller.getNick() + " QUIT :" + _para[0] + "\r\n";
    std::cout << "return " << _server.disconnectClient(_caller.getSocket()) << std::endl;
    std::list<Client *>::iterator it = _server.getClient().begin();
    for (; it != _server.getClient().end(); ++it)
        send((*it)->getSocket(), print.c_str(), strlen(print.c_str()), 0);
}
