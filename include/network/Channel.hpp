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
		std::map<int, std::string> _participantsFd; // 참여자들 담아두께여
		size_t	_participants;
		std::string _chnlPass;
		std::string _topic;

	public:
		Channel();
		Channel(std::string name);
		~Channel();

		bool _channelMode[10];

		// set
		void    setParticipants(size_t num, int fd, std::string name);
		void	setPass(std::string pass);
		
		// get

		// size_t		getParticipants();
		// int			getParticipants(size_t index); // fd뽑
		std::string getName();
		std::string getPass();

		std::map<int, std::string> &getParticipantsFd();
		int			getParticipantsKey(std::map<int, std::string>::iterator it);
		std::string	getParticipantsValue(std::map<int, std::string>::iterator it);
		size_t		getParticipantsSize();
};

#endif