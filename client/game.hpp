#include <iostream>
#include "../common.hpp"

using namespace std;

int printAct(char *buf) {
	msg Msg(buf);
	if (Msg.type == 'o') {
		cout << "kortti nro. " << buf << endl;
	} else cout << "Vastaanotettu viesti: " << buf << endl;
	return 1;
}
