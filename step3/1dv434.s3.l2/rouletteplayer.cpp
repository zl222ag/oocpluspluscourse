// rouletteplayer.cpp

#include "rouletteplayer.h"

bool RoulettePlayer::setGame(IGame* a_game) {// Sets the specific game for this player to play
	if (a_game->getID() != ROULETTE_ID) {
		return false;				// If the game specified is other than Roulette - return error
	}

	if (m_game != NULL && m_game != a_game) {
		delete m_game;				// If occupied by other game and not equal - delete it
	}

	m_game = a_game;
	return true;
}


bool RoulettePlayer::play(int a_choice) {// Tells player to play the game numberOfTimes times
	if (m_money < 0) {		// If no money left...
		return false;
	}

	if (a_choice == 0) {
		m_money = m_game->play("shoot", m_money);
		++m_betCount;
		return true;
	}

	if (a_choice == 1) {
		m_game->play("reload", 0);
		return true;
	}

	return false;
}
