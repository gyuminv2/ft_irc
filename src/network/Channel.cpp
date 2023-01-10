#include "../../include/network/Channel.hpp"

Channel::Channel() : _name(""), _participants(0), _chnlPass(""), _topicFlag(false) {}

Channel::Channel(std::string name): _name(name), _participants(0), _chnlPass("") {}

Channel::~Channel() {}

void    Channel::setParticipants(size_t num, int fd, std::string name) { _participantsFd.insert(std::make_pair(fd, name)); this->_participants += num;}

void	Channel::eraseParticipants(std::map<int, std::string>::iterator it)
{
    _participantsFd.erase(it);
    _participants -= 1;
}

void	Channel::setPass(std::string pass) { _chnlPass = pass; }

void	Channel::setTopic(std::string topic) { _topic = topic; }

void	Channel::setTopicNick(std::string nick) { _topicNick = nick; }

void	Channel::setTopicFlag(int flag) { _topicFlag = flag; }

void    Channel::setOper(std::string name) { _operName = name; }

std::string Channel::getName() { return _name; }

std::string Channel::getPass() { return _chnlPass; }

std::string Channel::getTopic() { return _topic; }

std::string	Channel::getTopicNick() { return _topicNick; }

bool    Channel::getTopicFlag() { return _topicFlag; }

std::map<int, std::string> &Channel::getParticipantsFd() { return _participantsFd; }

int			Channel::getParticipantsKey(std::map<int, std::string>::iterator it) { return (*it).first; }
std::string	Channel::getParticipantsValue(std::map<int, std::string>::iterator it) { return (*it).second; }
size_t		Channel::getParticipantsSize() { return _participantsFd.size(); }

std::string Channel::getOper() { return _operName; };
