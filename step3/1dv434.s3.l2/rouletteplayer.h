// rouletteplayer.h

#ifndef ROULETTE_PLAYER_H_
#define ROULETTE_PLAYER_H_
#include <cstdlib>

#include "IPlayer.h"
#include "IGame.h"

class RoulettePlayer: public IPlayer {
public:
	enum RouletteChoice {
		SHOOT = 0, RELOAD = 1
	};

	RoulettePlayer(int a_money) :
			m_game(NULL), m_money(a_money), m_betCount(0) {
	}

	// Sets the specific game for this player to play.
	virtual bool setGame(IGame *game);
	// Tells player to play the game with choice times
	virtual bool play(int choice);

	// Returns the amount of money still available for game
	virtual int getMoney() const {
		return m_money;
	}

	// Returns the total number of bets placed 
	// during object life time
	virtual int getBetCount() const {
		return m_betCount;
	}

private:
	IGame *m_game; // Points out the game to use (should be a Roulette Game)
	int m_money; // Shows the current amount of money available for playing
	int m_betCount; // Shows the number of bets placed so far
	static const int ROULETTE_ID = 21935; // ID assigned to the Roulette game
};

#endif // ROULETTE_PLAYER_H_
