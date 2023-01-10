#include "../../include/command/Command.hpp"

void Command::Numerics(int num, std::string name, std::string other)
{
	std::string print = ":127.0.0.1 " + std::to_string(num) + " " + _caller.getNick() + " ";

    (void) other;

	switch (num)
	{
		case 1:
			print += ":Welcome to the Internet Relay Network";
			break;
		case 2:
			print += ":Your host is ft_irc, running version 0.01";
			break;
		case 3:
			print += ":This server was created ~2022/12.31";
			break;
		case 4:
			print += ":ft_irc 0.01";
			break;
        case 5:
            print += ":are supported by this server";
            break;
        case 321:
            print += "Channel :Users  Name";
            break;
        case 332:
            print += name + " :" + other;
            break;
        case 333:
            print += name + " " + other;
            break;
        case 336:
            print += " " + name;
            break;
        case 353:
            print += "@ " + name + " :" + other;
            break;
        case 366:
            print += _caller.getNick() + " " + name + " :End of /Names list";
            break;
        case 381:
            print += ":You are now an IRC operator";
            break;
        case 401:
            print += name + " :No such nick/channel";
            break;
        case 403:
            print += name + " :No such channel";
            break;
        case 421:
            print += _cmd + " :Unknown command";
            break;
        case 431:
            print += ":No nickname given";
            break;
        case 432:
            print += ":Erroneous nickname";
            break;
        case 433:
            print += ":Nickname is already in use";
            break;
        case 442:
            print += name + " :You're not on that channel";
            break;
        case 461:
            print += ":Not enough parameters";
            break;
		case 462:
			print += ":You may not reregister";
			break;
		case 464:
			print += ":Password incorrect";
			break;
        case 475:
            print += name + " :Cannot join channel (+k)";
            break;
        case 482:
            print += name + " :You're not channel operator";
            break;
        case 491:
            print += ":No O-lines for your host";
            break;

		default:
			break;
	}
    print += "\r\n";
    if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}
