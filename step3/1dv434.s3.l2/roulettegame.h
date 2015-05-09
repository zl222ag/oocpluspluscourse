#ifndef ROULETTE_GAME_H_
#define ROULETTE_GAME_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "IGame.h"

using std::cout;
using std::endl;

class RouletteGame : public IGame {
	static const int ROULETTE_GAME_ID = 21935;
	static const unsigned char NUMBER_OF_CHAMBERS = 6;
	unsigned char m_currentChamber;
	unsigned char m_shootCount;

public:
	RouletteGame() {
		srand((unsigned) time(NULL));
		randomizeCurrentChamber();
	}

	// Randomizes the "current gun chamber".
	void randomizeCurrentChamber() {
		m_currentChamber = (unsigned char) rand() % NUMBER_OF_CHAMBERS;
		m_shootCount = (unsigned char) 0;
	}

	// reload, shoot, what more to it?
	// returns 0 on losing.
	// returns a_amount back when reloading and reloads (unless a_amount < 0).
	// player profits if not dead after shooting (otherwise 0)
	// (if a_amount > 0).
	/* virtual */ int play(char* a_bet, int a_amount);

	/* virtual */ int getID() const {
		return ROULETTE_GAME_ID;
	}
};

#endif // ROULETTE_GAME_H_
