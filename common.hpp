#ifndef BANG_COMMON_HPP
#define BANG_COMMON_HPP

#define PORT 6661
#define BUFFER_SIZE 512
#define VERSION 0.23

#include <vector>
#include <sstream>

#define DEBUG(str) std::cout << "DEBUG, " << __LINE__ << ": [" << str << "]" << __FILE__ << std::endl;
#define INPUT(key, str) std::cout << key << ": " << __LINE__ << " - [" << str << "]" << std::endl;
#define OUTPUT(key, str) std::cout << key << ": " << __LINE__ << " - [" << str << "]" << std::endl;

unsigned minPlayersInGame = 3;

template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <class F, class T>
std::string toMsg (char type, F from, T to, std::string str){
    std::stringstream ss;
    ss << type << from << to << str.c_str();
    return ss.str();
}
template <class F, class T, class S>
std::string toMsg (char type, F from, T to, S str){
    std::stringstream ss;
    ss << type << from << to << str;
    return ss.str();
}

enum ERRORS {
	ERRNO_NOT_ENOUGH_ARGS,
	ERRNO_NOT_VALID_ADDR,
	ERRNO_CANT_CONNECT,
	ERRNO_CANT_RECEIVE,
	ERRNO_CANT_SEND
};

enum CARDS {

};

enum MSG_TYPE {		//Toimintamerkit:
	TEXT		= 'M',
	MESSAGE		= 'M',
	ACTION		= 'A',
	DIE			= 'D',
	SHUTDOWN	= 'S',
	ENDTURN		= 'E',
	TURN		= 'T',
	PING		= 'P',
	CARD		= 'C'
};

struct msg { // Parsitut viestit muotoa typesendertargetoptions[....]
	MSG_TYPE	type;
	short		sender, target;
	char*		buf;
	std::string	data;
};

#endif
