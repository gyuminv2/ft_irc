#include "../../include/command/Command.hpp"

void Command::privmsgMessage(std::string name, std::string msg)
{
	Channel tmp;
	int flag = 0;
	for (std::list<Channel>::iterator it = _server.getChannel().begin(); it != _server.getChannel().end(); it++)
	{
		if (name == (*it).getName())
		{
			tmp = (*it);
			flag = 1;
			break ;
		}
	}
	std::map<int, std::string>::iterator it = tmp.getParticipantsFd().begin();

	if (flag == 0)
	{
		this->Numerics(401);
		return ;
	}
	for (size_t i = 0; i < tmp.getParticipantsSize(); i++, it++)
	{
		std::string print = ":" + _caller.getNick() + " PRIVMSG " + name + " :" + msg;
		print += "\r\n";
		std::cout << "print[" << print << "]";
		if (_caller.getSocket() == tmp.getParticipantsKey(it))
			continue ;
		if (send(tmp.getParticipantsKey(it), print.c_str(), strlen(print.c_str()), 0) == -1)
			throw std::runtime_error("send 에러");
	}
}

void Command::privmsgMessage(std::string name, std::string msg, int fd)
{
	std::string print = ":" + _caller.getNick() + " PRIVMSG " + name + " :" + msg;
	print += "\r\n";
    std::cout << "print[" << print << "]";
    if (send(fd, print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}

int	Command::getNickFd(std::string nick, std::list<Client *> clnt)
{
	for (std::list<Client *>::iterator it = clnt.begin(); it != clnt.end(); it++)
	{
		if ((*it)->getNick() == nick)
			return ((*it)->getSocket());
	}
	return (_server.getFdmax());
}

void Command::Privmsg()
{
	std::string msg;

	if (_paraNum == 1)
		return ;
	if (_parsingPara[0].find('#') == std::string::npos)
	{
		this->privmsgMessage(_parsingPara[0], _parsingPara[1], getNickFd(_parsingPara[0], _server.getClient()));
	}
	else
	{
		this->privmsgMessage(_parsingPara[0], _parsingPara[1]);
	}
}
