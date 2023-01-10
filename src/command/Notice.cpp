#include "../../include/command/Command.hpp"

void Command::noticeMessage(std::string name, std::string msg)
{
	Channel tmp;
	for (std::list<Channel>::iterator it = _server.getChannel().begin(); it != _server.getChannel().end(); it++)
	{
		if (name == (*it).getName())
		{
			tmp = (*it);
			break ;
		}
	}
	std::map<int, std::string>::iterator it = tmp.getParticipantsFd().begin();

	for (size_t i = 0; i < tmp.getParticipantsSize(); i++, it++)
	{
		std::string print = ":" + _caller.getNick() + " NOTICE " + name + " :" + msg;
		print += "\r\n";
		std::cout << "print[" << print << "]";
		if (_caller.getSocket() == tmp.getParticipantsKey(it))
			continue ;
		if (send(tmp.getParticipantsKey(it), print.c_str(), strlen(print.c_str()), 0) == -1)
			throw std::runtime_error("send 에러");
	}
}

void Command::Notice()
{
	std::string msg;

	if (_paraNum == 1)
		return ;
	if (_parsingPara[0].find('#') != std::string::npos)
	{
		std::cout << "유저!!!!!!1\n";
		this->noticeMessage(_parsingPara[0], _parsingPara[1]);
	}
	else
	{
	}
}
