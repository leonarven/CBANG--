//
// game.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 Miro Nieminen (leonarven@gmail.com)
//

#ifndef GAME_HPP
#define GAME_HPP

#inlcude <vector>

using namespace std;

enum KORTTI {
	BYROKRAATTI,
}

struct kortti {

}

class pelaaja {
	public:
	pelaaja pelaaja() {}
	vector<kortti> kortit
}

class moottori {
	public:
		int vuoro;
	private:
		vector<pelaaja> pelaajat;
}
#endif // GAME_HPP

