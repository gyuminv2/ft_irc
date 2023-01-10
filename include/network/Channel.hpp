#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>

enum Channel_mode
{
	channel_o = 0,
	channel_p,
	channel_s,
	channel_i,
	channel_t,
	channel_m,
	channel_v,
	channel_l,
	channel_b,
	channel_k
};

class Channel
{
	private:
		std::string _name;
		std::map<int, std::string> _participantsFd;
		size_t	_participants;
		std::string _chnlPass;
		std::string _topic;
		std::string _topicNick;
		bool	_topicFlag;
		std::string _operName;

	public:
		Channel();
		Channel(std::string name);
		~Channel();

		bool _channelMode[10];

		void    setParticipants(size_t num, int fd, std::string name);
		void	eraseParticipants(std::map<int, std::string>::iterator it);
		void	setPass(std::string pass);
		void	setTopic(std::string topic);
		void	setTopicNick(std::string nick);
		void	setTopicFlag(int flag);
		void    setOper(std::string name);

		std::string getName();
		std::string getPass();
		std::string	getTopic();
		std::string	getTopicNick();
		bool		getTopicFlag();

		std::map<int, std::string> &getParticipantsFd();
		int			getParticipantsKey(std::map<int, std::string>::iterator it);
		std::string	getParticipantsValue(std::map<int, std::string>::iterator it);
		size_t		getParticipantsSize();
		std::string getOper();
};

#endif
