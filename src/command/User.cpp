#include "../../include/command/Command.hpp"

void Command::User()
{
	if (_caller.getnickState() == false)
		return ;
	if (_paraNum < 4)
	{
		this->Numerics(461);
		return ;
	}
	if (!_caller.getUser().empty() || !_caller.getReal().empty())
	{
		this->Numerics(462);
		return ;
	}
	if (_parsingPara[1] != "0" || _parsingPara[2] != "*" || 1 > _parsingPara[0].length())
	{
		this->Numerics(461);
		return ;
	}
	if ( _parsingPara[0].length() > 9)
		_parsingPara[0].resize(9);
	_caller.setUser(_parsingPara[0]);
	_caller.setReal(_parsingPara, _paraNum);
	_caller.setuserState(true);
}
