#include "../../include/command/Command.hpp"

void    Command::Nick()
{
    if (_paraNum == 0)
    {
        this->Numerics(431);
        return ;
    }
    if (isdigit(_parsingPara[0].at(0)) == true)
    {
        this->Numerics(432);
        return ;
    }
    std::list<Client *>::iterator it = _server.getClient().begin();
    for (; it != _server.getClient().end(); ++it)
    {
        if ((*it)->getNick() == _parsingPara[0])
        {
            this->Numerics(433);
            return ;
        }
    }
    _caller.setNick(_parsingPara[0]);
    _caller.setnickState(true);
}
