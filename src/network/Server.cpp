#include "../../include/network/Server.hpp"

Server::Server(const std::string port, const std::string pass): _port(port), _pass(pass) {}

Server::~Server() {}

void    Server::makeSock()
{
	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("socket 에러");

	int opt = 1;
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("setsockopt 에러");

	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl 에러");

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(stoi(getPort()));

	if (bind(_sock, (struct sockaddr *) &address, sizeof(address)) == -1)
		throw std::runtime_error("bind 에러");

	if (listen(_sock, 1024) == -1)
		throw std::runtime_error("listen 애러");
	FD_ZERO(&_read_fd);
	FD_SET(_sock, &_read_fd);
	_fd_max = _sock;
}

void    Server::loop()
{
	std::string	input;
	int clnt_fd;
	struct sockaddr_in clnt_adr;

	while(1)
	{
		_cp_read = _read_fd;
		if (select(_fd_max + 1, &_cp_read, 0, 0, 0) == -1)
			throw std::runtime_error("select 에러");
		for (int i = 0; i < _fd_max + 1; i++)
		{
			if (FD_ISSET(i, &_cp_read))
			{
				if (i == _sock)
				{
					socklen_t adr_sz = sizeof(clnt_adr);
					if ((clnt_fd = accept(_sock, (struct sockaddr *)&clnt_adr, &adr_sz)) == -1)
						throw std::runtime_error("accept 에러");
					Client *clnt = new Client(clnt_fd);
					_clnt.push_back(clnt);
					FD_SET(clnt_fd, &_read_fd);
					if (_fd_max < clnt_fd)
						_fd_max = clnt_fd;
				}
				else
				{
					char received[256];
					int len;
					if ((len = recv(i, received, sizeof(received), 0)) <= 0)
					{
						received[len] = 0;
						if (len == 0)
						{
							std::cout << "@disconnect@ Client fd: [" << this->disconnectClient(i) << "]\n";
							continue;
						}
						else
							throw std::runtime_error("recv 에러");
					}
					received[len] = 0;
					input.clear();
					input.append(received);
					Client *user = this->getclientSock(i);
					if (user->getSocket() > 0)
					{
						Command cmd(input, this->getPass(), *user, *this);
						cmd.execute();
					}
					input.clear();
				}
			}
		}
	}
	close(_sock);
	close(clnt_fd);
}

int	Server::disconnectClient(int fd)
{
	std::cout << "disconnect " << fd << std::endl;
	for (std::list<Client *>::iterator it = _clnt.begin(); it != _clnt.end(); ++it)
	{
		if ((*it)->getSocket() == fd)
		{
			FD_CLR(fd, &_read_fd);
			for (std::list<Channel>::iterator ite = _chnl.begin(); ite != _chnl.end(); ite++)
			{
				std::string print = ":" + (*it)->getNick() + "!" + (*it)->getUser() + "@127.0.0.1" + " PART " + (*ite).getName() + "\r\n";
				std::map<int, std::string>::iterator iter = (*ite).getParticipantsFd().begin();
				for (; iter != (*ite).getParticipantsFd().end(); iter++)
				{
					std::cout << "out it " << (*ite).getParticipantsKey(iter) << std::endl;
					if ((*ite).getParticipantsKey(iter) != fd)
					{
						std::cout << "send: " << (*ite).getParticipantsKey(iter) << std::endl;
						if (send((*ite).getParticipantsKey(iter), print.c_str(), strlen(print.c_str()), 0) == -1)
							throw std::runtime_error("send error");
					}
				}
			}
			for (std::list<Channel>::iterator ite =_chnl.begin(); ite !=_chnl.end(); ite++)
			{
				(*ite).getParticipantsFd().erase(fd);
			}
			_clnt.remove(*it);
			delete *it;
			close(fd);
			if (_clnt.empty() == true)
				_fd_max = _sock;
			else if (_fd_max == fd)
				this->chgFdmax();
			return fd;
		}
	}
	return -1;
}

void	Server::chgFdmax()
{
	for (std::list<Client *>::iterator it = _clnt.begin(); it != _clnt.end(); ++it)
		if ((*it)->getSocket() > _fd_max)
			_fd_max = (*it)->getSocket();
}

Client    *Server::getclientSock(int fd)
{
	for (std::list<Client *>::iterator it = _clnt.begin(); it != _clnt.end(); ++it)
		if ((*it)->getSocket() == fd)
			return (*it);
	return NULL;
}

std::list<Client *> &Server::getClient() { return _clnt; }

std::list<Channel> &Server::getChannel() { return _chnl; }

int	Server::getSock() { return _sock; }

std::string Server::getPort() { return _port; }

std::string Server::getPass() { return _pass; }

int             Server::getFdmax() { return _fd_max; }
