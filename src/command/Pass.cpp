#include "../../include/command/Command.hpp"

void Command::Pass()
{
    std::cout << "pass: " << _pass << ", para: " << _para << ";" ;

    if (_caller.getpassState() == true)
    {
        this->Numerics(462);
        return ;
    }
    if (_pass != _para)
    {
        this->Numerics(464);
        return ;
    }
    else
        _caller.setpassState(true);
}
