#ifndef BANG_COMMON_HPP
#define BANG_COMMON_HPP

#define PORT 6661
#define BUFFER_SIZE 6661

#include <vector>

enum ERRORS {
	ERRNO_TOO_LESS_ARGS,
	ERRNO_NOT_VALID_ADDR,
	ERRNO_CANT_CONNECT,
	ERRNO_CANT_RECEIVE,
	ERRNO_CANT_SEND
};

enum CARDS {

};

enum ACTION {
	NONE,
	BANG
};

enum MSG_TYPE {
	TEXT,
	ACTION
};

struct msg {
	MSG_TYPE type;
	char* buf;
	std::vector<char> options;
};

#endif
