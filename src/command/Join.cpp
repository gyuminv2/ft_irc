#include "../../include/command/Command.hpp"


void	Command::joinMessage(std::string name)
{
	std::string print = ":" + _caller.getNick() + "!" + _caller.getUser() + "@127.0.0.1" + " JOIN " + name + "\r\n";
	if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러1");
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
	for (; it != tmp.getParticipantsFd().end(); it++)
	{
		if (tmp.getParticipantsFd().end() != it && tmp.getParticipantsKey(it) != _caller.getSocket())
		{
			print = ":" + _caller.getNick() + "!" + _caller.getUser() + "@127.0.0.1" + " JOIN " + name + "\r\n";
			if (send(tmp.getParticipantsKey(it) , print.c_str(), strlen(print.c_str()), 0) == -1)
       			throw std::runtime_error("send 에러3");
		}
		this->Numerics(353, name, tmp.getParticipantsValue(it));
		this->Numerics(366, name);
	}
	if (tmp.getTopicFlag() == true)
	{
		this->Numerics(332, name, tmp.getTopic());
		this->Numerics(333, name, tmp.getTopicNick());
	}
}

void    Command::Join()
{
	std::string chnlName = _parsingPara[0];
	std::string chnlPass = _parsingPara[1];
	size_t nameStart = 0;
	size_t passStart = 0;
	size_t namePos = chnlName.find(',');
	size_t passPos = chnlPass.find(',');

	while (namePos != std::string::npos)
	{
		chnlName = parseComma(_parsingPara[0], nameStart, namePos);
		chnlPass = parseComma(_parsingPara[1], passStart, passPos);

		if (chnlName.find(0x07) != std::string::npos || chnlName.find(',') != std::string::npos)
		{
			this->Numerics(403);
			continue ;
		}
		if (checkChannel_server(chnlName) == false)
		{
			Channel instance(chnlName);
			instance.setPass(chnlPass);
			instance.setParticipants(1, _caller.getSocket(), _caller.getNick());
			_caller.addChannel(instance);
			_server.getChannel().push_back(instance);
			this->joinMessage(chnlName);
		}
		else
		{
			std::list<Channel> &chnl = _server.getChannel();

			for (std::list<Channel>::iterator it = chnl.begin(); it != chnl.end(); it++)
			{
				if ((*it).getName() == chnlName)
				{
					if ((*it).getPass() == chnlPass || (*it).getPass().empty())
					{
						(*it).setParticipants(1, _caller.getSocket(), _caller.getNick());
						this->joinMessage(chnlName);
					}
					else
						this->Numerics(475, chnlName);
				}
			}
		}
	}

	chnlName = parseComma(_parsingPara[0], nameStart, namePos);
	chnlPass = parseComma(_parsingPara[1], passStart, passPos);
	if (chnlName.empty())
	{
		this->Numerics(403, chnlName);
		return ;
	}
	if (!checkChannel_server(chnlName))
	{
		Channel instance(chnlName);
		instance.setPass(chnlPass);
		instance.setParticipants(1, _caller.getSocket(), _caller.getNick());
		instance.setOper(_caller.getNick());
		_caller.addChannel(instance);
		_server.getChannel().push_back(instance);
		this->joinMessage(chnlName);

		this->modeMessage1(chnlName, '+', _caller.getNick());
	}
	else
	{
		std::list<Channel> &chnl = _server.getChannel();

		for (std::list<Channel>::iterator it = chnl.begin(); it != chnl.end(); it++)
		{
			if ((*it).getName() == chnlName)
			{
				if ((*it).getPass() == chnlPass || (*it).getPass().empty())
				{
					(*it).setParticipants(1, _caller.getSocket(), _caller.getNick());
					_caller.addChannel((*it));
					this->joinMessage(chnlName);
					this->modeMessage2(chnlName, '+', (*it).getOper());
				}
				else
					this->Numerics(475, chnlName);
			}
		}
	}
}
