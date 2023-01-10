#include "../../include/command/Command.hpp"

void Command::topciMessage(std::string name, std::string topic)
{
    std::string print = ":" + _caller.getNick() + "!" + _caller.getUser() + "@127.0.0.1" + " TOPIC " + name + " :" + topic;
	print += "\r\n";
	if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}

void Command::Topic()
{
	std::string chnlName = _parsingPara[0];

	std::list<Channel> &chnl = _server.getChannel();

	std::list<Channel>::iterator it = chnl.begin();
    for (; it != chnl.end(); it++)
	{
		if ((*it).getName() == chnlName)
		{
			this->topciMessage(chnlName, _parsingPara[1]);
			(*it).setTopicFlag(true);
			(*it).setTopicNick(_caller.getNick());
			(*it).setTopic(_parsingPara[1]);
            return ;
		}
	}
    if (it == chnl.end())
		this->Numerics(401);
}
