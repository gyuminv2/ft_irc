#include "../../include/command/Command.hpp"
#include <iostream>

Command::Command(std::string input, std::string pass, Client &caller, Server &server): _paraNum(0), _caller(caller), _server(server)
{
	std::cout << input << std::endl;
	input_parse(input);
	_pass = pass;
}

Command::~Command() {}

void Command::input_parse(std::string input)
{
	size_t ret_pos2 = input.find("\r\n");
	if (ret_pos2 != std::string::npos)
		input = input.substr(0, ret_pos2);

	size_t ret_pos = input.find("\n");
	if (ret_pos != std::string::npos)
		input = input.substr(0, ret_pos);

	size_t pos = input.find(' ');
	if (pos != std::string::npos)
	{
		_cmd = input.substr(0, pos);
		_para = input.substr(pos + 1);
		if (_cmd == _para)
		{
			std::cout << "NO parameter\n";
			return ;
		}
		else
			para_parse(_para);
	}
	else
		_cmd = input;
}

void Command::para_parse(std::string para)
{
	size_t i = 0;
	size_t j = -1;
	size_t pos = para.find(' ');

	if (para.empty())
	{
		_paraNum = 0;
		return ;
	}
	while (pos != std::string::npos)
	{
		_parsingPara[++j] = para.substr(i, pos - i);
		i = pos + 1;
		pos = para.find(' ', i);
	}
	_parsingPara[++j] = para.substr(i, pos - i);
	_paraNum += j + 1;
}

void Command::execute()
{
	if (_cmd == "PASS")
		Pass();
	else if (_caller.getpassState() == true)
	{
		if (_cmd == "NICK")
			Nick();
		else if (_cmd == "USER")
		{
			User();
			if (_caller.getuserState() == false || _caller.getaccessState() == false)
			{
				this->Numerics(1);
				this->Numerics(2);
				this->Numerics(3);
				this->Numerics(4);
				this->Numerics(5);
				_caller.setaccessState(true);
			}
		}
		else if (_cmd == "QUIT")
			Quit();
		else if (_cmd == "OPER")
			Oper();
		else if (_cmd == "JOIN")
			Join();
		else if (_cmd == "PART")
			Part();
		else if (_cmd == "TOPIC")
			Topic();
		else if (_cmd == "NAMES")
			Names();
		else if (_cmd == "LIST")
			List();
		else if (_cmd == "INVITE")
			Invite();
		else if (_cmd == "KICK")
			Kick();
		else if (_cmd == "MODE")
			Mode();
		else if (_cmd == "PRIVMSG")
			Privmsg();
		else if (_cmd == "NOTICE")
			Notice();
		else if (_cmd == "PONG")
			return ;
		else if (_cmd.empty())
			return ;
		else
			this->Numerics(421);
	}
	else
		std::cout << "ERROR PASS COMMAND!" << std::endl;
}

bool    Command::checkClient(std::string name)
{
	std::list<Client *>::iterator it = _server.getClient().begin();
    for (; it != _server.getClient().end(); ++it)
    {
        if ((*it)->getNick() == name)
            return true;
    }
	return false;
}

bool    Command::checkChannel_server(std::string name)
{
    std::list<Channel>::iterator it = _server.getChannel().begin();
    for (; it != _server.getChannel().end(); it++)
    {
        if ((*it).getName() == name)
            return true;
    }
    return false;
}

bool    Command::checkChannel_caller(std::string name)
{
    std::list<Channel>::iterator it = _caller.getChannel().begin();
    for (; it != _caller.getChannel().end(); it++)
    {
        if ((*it).getName() == name)
            return true;
    }
    return false;
}

std::string Command::parseComma(std::string origin, size_t &start, size_t &pos)
{
	std::string parsedString = origin.substr(start, pos - start);
	start = pos + 1;
	pos = origin.find(',', start);
	return parsedString;
}
