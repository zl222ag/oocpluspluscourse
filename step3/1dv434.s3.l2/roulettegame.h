#ifndef ROULETTE_GAME_H_
#define ROULETTE_GAME_H_
#include <iostream>
#include "IGame.h"

using std::cout;
using std::endl;

class RouletteGame : public IGame {
	static const int ROULETTE_GAME_ID = 21935;

public:
	virtual int play(char* a_bet, int a_amount) {
		cout << a_bet << endl;
		return a_amount;
	}

	virtual int getID() const {
		return ROULETTE_GAME_ID;
	}
};

#endif // ROULETTE_GAME_H_
