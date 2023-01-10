#include "../../include/command/Command.hpp"

void	Command::showChannel(std::string name, std::list<Channel> chnl)
{
	for (std::list<Channel>::iterator it = chnl.begin(); it != chnl.end(); it++)
	{
		if (name == (*it).getName())
		{
			this->Numerics(321);
			std::string print = ":127.0.0.1 322 " + _caller.getNick() + " " + (*it).getName() + " " + std::to_string((*it).getParticipantsSize()) + " :" + (*it).getTopic() + "\r\n";
			if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
				std::runtime_error("send error");
			print = ":127.0.0.1 323 " + _caller.getNick() + " :End of /LIST\r\n";
				if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
					std::runtime_error("send error");
		}
	}
}

void	Command::List()
{
	if (_paraNum == 0)
	{
		for (std::list<Channel>::iterator it = _server.getChannel().begin(); it != _server.getChannel().end(); it++)
		{
			this->Numerics(321);
			std::string print = ":127.0.0.1 322 " + _caller.getNick() + " " + (*it).getName() + " " + std::to_string((*it).getParticipantsSize()) + " :" + (*it).getTopic() + "\r\n";
			if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
				std::runtime_error("send error");
		}
		std::string print = ":127.0.0.1 323 " + _caller.getNick() + " :End of /LIST\r\n";
			if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
				std::runtime_error("send error");
	}
	else if (_paraNum == 1)
	{
		if (_parsingPara[0].find('#') == std::string::npos)
			return ;
		std::string chnl;
		size_t start = 0;
		size_t pos = _parsingPara[0].find(',');

		while (pos != std::string::npos)
		{
			chnl = parseComma(_parsingPara[0], start, pos);
			showChannel(chnl, _server.getChannel());
		}
		chnl = parseComma(_parsingPara[0], start, pos);
		showChannel(chnl, _server.getChannel());
	}
}
