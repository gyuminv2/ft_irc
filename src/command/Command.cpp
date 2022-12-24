#include "../../include/command/Command.hpp"
#include <iostream>

// Command::Command(std::string input, std::string pass, Client &caller): _paraNum(0), _caller(caller)
// {
//     std::cout << input << std::endl;
//     input_parse(input);
//     _pass = pass + "\r\n";
// }

Command::Command(std::string input, std::string pass, Client &caller, Server &server): _paraNum(0), _caller(caller), _server(server)
{
	std::cout << input << std::endl;
	input_parse(input);
	_pass = pass + "\r\n";
}

Command::~Command() {}

void Command::input_parse(std::string input)
{
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
}

void Command::para_parse(std::string para)
{
	size_t i = 0;
	size_t j = -1;  // parsingPara[index]
	size_t pos = para.find(' ');

	if (para == "\r\n")
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
			if (_caller.getaccessState() == false)
			{
				this->Numerics(1);
				// this->Numerics(2);
				// this->Numerics(3);
				// this->Numerics(4);
				_caller.setaccessState(true);
			}
		}
		else if (_cmd == "JOIN")
			Join();
	   	else if (_cmd == "LIST")
			List();
		else
			std::cout << "NO MATCHING COMMAND!" << std::endl;

		/*
		OPER
		QUIT
		JOIN
		PART
		TOPIC
		NAMES
		LIST
		Invite
		KICK
		Help
		MODE
		PRIVMSG
		Notice
		Who?
		*/
	}
}