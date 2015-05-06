#include "roulettegame.h"
#include <compare.h>

// reload, shoot, what more to it?
// returns 0 on losing.
// returns a_amount back when reloading.
// player profits if not dead after shooting.
int RouletteGame::play(char* a_bet, int a_amount) {
	if (Compare::equal(a_bet, "reload")) {
		randomizeCurrentChamber();
		return a_amount;
	}

	if (Compare::equal(a_bet, "shoot")) {
		m_currentChamber =
			(unsigned char) ((m_currentChamber + 1) % NUMBER_OF_CHAMBERS);

		if (m_currentChamber == NUMBER_OF_CHAMBERS - 1) {
			randomizeCurrentChamber();
			return 0;
		}
		++m_shootCount;

		return a_amount * m_shootCount * 1.5f;
	}

	return a_amount;
}
