#ifndef BANG_COMMON_HPP
#define BANG_COMMON_HPP

#define PORT 6661
#define BUFFER_SIZE 6661

#include <vector>

enum CARDS {

};

enum ACTION {
	NULL,
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
