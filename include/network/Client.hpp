#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <list>
# include "./Channel.hpp"

enum User_mode
    {
        user_a = 0,
        user_i,
        user_w,
        user_r,
        user_o,
        user_O,
        user_s
    };

class Client
{
    private:
    int _fd;
    std::string _nick;
    std::string _user;
    std::string _real;
    std::string _pass;

    std::list<Channel>		_channelList;

    bool _passState;
    bool _nickState;
    bool _userState;
    bool _accessState;
    bool _servOper;


    public:
        Client(int fd);
        ~Client();

        bool _userMode[7];

        int getSocket();
        std::string getNick();
        bool getpassState();
        bool getnickState();
        bool getuserState();
        bool getaccessState();
        bool getservOper();

        void addChannel(Channel &chnl);
        void removeChannel(std::list<Channel>::iterator it);
        void setpassState(bool state);
        void setnickState(bool state);
        void setuserState(bool state);
        void setaccessState(bool state);
        void setservOper(bool state);
        void setNick(std::string nick);
        void setUser(std::string user);
        void setReal(std::string _parsingPara[9], size_t _paraNum);
        std::string getUser();
        std::string getReal();

        std::list<Channel> &getChannel();
};

#endif
