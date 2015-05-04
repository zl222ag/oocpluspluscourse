#include <cstdlib>
#include "IGame.h"

class Wrapper : public IGame, private CrapGame {
public:
	virtual int play(char *bet, int amount) {
		return m_game.play(bet, amount);
	}

	virtual int getID() const { return m_game.getID(); }

private:
	CrapGame m_game;
};
