#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>

#include <iostream>
#include <algorithm>
#include <sys/poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <sys/time.h>
#include "../in.h"
#include "./Client.hpp"
#include "./../command/Command.hpp"
#include <list>

class Server
{
    private:
        int         _sock;
        std::string _port;
        std::string _pass;

        fd_set      _read_fd, _cp_read;
        int         _fd_max;

        std::list<Client *> _clnt;
        std::list<Channel> _chnl;
    public:
        Server(const std::string port, const std::string pass);
        ~Server();

        void    makeSock();
        void    loop();

        int	disconnectClient(int fd);
        void chgFdmax();


        Client    *getclientSock(int fd);
        std::list<Client *> &getClient();
        std::list<Channel>  &getChannel();
        int             getSock();
        std::string     getPort();
        std::string     getPass();
        int             getFdmax();
};
#endif
