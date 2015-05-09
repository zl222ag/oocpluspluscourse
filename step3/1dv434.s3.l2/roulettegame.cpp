#include "roulettegame.h"
#include <compare.h>

// reload, shoot, what more to it?
// returns 0 on losing.
// returns a_amount back when reloading and reloads (unless a_amount < 0).
// player profits if not dead after shooting (otherwise 0) (if a_amount > 0).
int RouletteGame::play(char* a_bet, int a_amount) {
	if (a_amount < 1 || a_bet == NULL) {
		return 0;
	}

	if (Compare::equal(a_bet, "reload")) {
		randomizeCurrentChamber();
		return a_amount;
	}

	if (Compare::equal(a_bet, "shoot")) {
		m_currentChamber = (unsigned char) ((m_currentChamber + 1)
				% NUMBER_OF_CHAMBERS);

		if (m_currentChamber == NUMBER_OF_CHAMBERS - 1) {
			randomizeCurrentChamber();
			return 0;
		}
		++m_shootCount;

		return a_amount * m_shootCount * 1.5f;
	}

	return a_amount;
}
