//
// game.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Miro Nieminen (leonarven@gmail.com)
//

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

using namespace std;

enum KORTTI {

};

struct kortti {

};

class pelaaja {
	public:
	pelaaja() {}
	vector<kortti> kortit;
};

class moottori {
	public:
		int vuoro;
	private:
		vector<pelaaja> pelaajat;
};
#endif // GAME_HPP

