#ifndef BANG_COMMON_HPP
#define BANG_COMMON_HPP

enum CARDS {

};

enum ACTION {

};

class msg {
	public:
		msg(char *_buf) : buf(_buf) {

		}
		char type;
	private:
		char* buf;
};


#endif
