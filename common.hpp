#ifndef BANG_COMMON_HPP
#define BANG_COMMON_HPP

#define PORT 6661
#define BUFFER_SIZE 6661

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
