#include "../../include/command/Command.hpp"

void Command::Invite()
{
    std::string target = _parsingPara[0];
    std::string chnlName = _parsingPara[1];

    std::string print = ":" + _caller.getNick() + "!" + _caller.getUser() + "@127.0.0.1" + " INVITE " + target + chnlName;
    print += "\r\n";
	if (send(_caller.getSocket(), print.c_str(), strlen(print.c_str()), 0) == -1)
        throw std::runtime_error("send 에러");
}
