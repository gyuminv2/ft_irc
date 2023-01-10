#include "../../include/command/Command.hpp"

void	Command::modeMessage1(std::string name, char flag, std::string user)
{
    (void) user;
    std::string print = ":" + _caller.getNick() + "!" + _caller.getUser() + "@127.0.0.1" + " MODE " + name + " " + flag + "o " + _caller.getNick() + "\r\n";
    if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}

void	Command::modeMessage2(std::string name, char flag, std::string user)
{
	std::string print = ":" + user + "!" + _caller.getUser() + "@127.0.0.1" + " MODE " + name + " " + flag + "o " + user + "\r\n";
    if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}

void	Command::modeMessage3(std::string name, char flag, std::string user)
{
    std::string print = ":" + user + "!" + _caller.getUser() + "@127.0.0.1" + " MODE " + name + " " + flag + "o " + user + "\r\n";
    if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");

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
		if (send(tmp.getParticipantsKey(it) , print.c_str(), strlen(print.c_str()), 0) == -1)
        	throw std::runtime_error("send 에러");
	}
}

void Command::Mode()
{
    if (_paraNum == 0)
    {
        this->Numerics(461);
        return ;
    }
    if (checkClient(_parsingPara[0]) == false && checkChannel_server(_parsingPara[0]) == false)
    {
        this->Numerics(401);
        return ;
    }
    if (_parsingPara[0].at(0) == '#')
        _mode = 'c';
    else
        _mode = 'u';
    if (_caller.getNick() != _parsingPara[0] && _mode == 'u')
    {
        this->Numerics(502);
        return ;
    }
    if (_parsingPara[1].at(0) == '+' || _parsingPara[1].at(0) == '-')
    {
        std::string modestring;
        char        flag = _parsingPara[1].at(0);
        size_t mode_num = 0;
        std::string::iterator it = _parsingPara[1].begin();
        while (it != _parsingPara[1].end())
        {
            if (*it != '+' && *it != '-')
            {
                modestring += *it;
                mode_num++;
            }
            it++;
        }
        if (mode_num == 0)
            return ;
        for (size_t i = 0; i < mode_num; i++)
        {
            if (excute_mode(modestring.at(i), _mode, flag) == false)
                this->Numerics(501);
        }
    }
    else
    {
        for (size_t i = 1; i < _parsingPara[1].length(); i++)
        {
            if (excute_mode(_parsingPara[1].at(i), _mode) == false)
                this->Numerics(501);
        }
    }
}

bool Command::excute_mode(char mode, char c, char flag)
{
    if (c == 'u')
    {
        if (mode == 'o')
        {
            _caller._userMode[user_o] = true;
            return true;
        }
    }
    else if (c == 'c')
    {
        std::list<Channel>::iterator it = _server.getChannel().begin();
        for (; it != _server.getChannel().end(); it++)
        {
            if ((*it).getName() == _parsingPara[0])
            {
                if (mode == 'o' && flag == '+')
                {
                    (*it)._channelMode[channel_o] = true;
                    this->modeMessage3((*it).getName(), flag, _parsingPara[2]);
                    return true;
                }
                else if (flag == '-')
                {
                    (*it)._channelMode[channel_o] = true;
                    this->modeMessage3((*it).getName(), flag, _parsingPara[2]);
                    return true;
                }
            }
        }
    }
    return false;
}
