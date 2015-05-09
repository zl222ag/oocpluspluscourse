// rouletteplayer.cpp

#include "rouletteplayer.h"

// Sets the specific game for this player to play.
bool RoulettePlayer::setGame(IGame* a_game) {
	// If the game specified is other than Roulette - return error
	if (a_game->getID() != ROULETTE_ID) {
		return false;
	}

	// If occupied by other game and not equal - delete it
	if (m_game != NULL && m_game != a_game) {
		delete m_game;
	}

	m_game = a_game;
	return true;
}

// Tells player to play the game with choice times
bool RoulettePlayer::play(int a_choice) {
	// If no money left...
	if (m_money < 0) {
		return false;
	}

	if (a_choice == RouletteChoice::SHOOT) {
		m_money = m_game->play("shoot", m_money);
		++m_betCount;
		return true;
	}

	if (a_choice == RouletteChoice::RELOAD) {
		// Reloading, gives necessary amount of money!
		m_game->play("reload", 1);
		return true;
	}

	return false;
}
