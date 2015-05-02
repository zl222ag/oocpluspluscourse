#include <iostream>
#include <cstdlib>
#include "CrapGame.h"
#include "CrapPlayer.h"
#include "roulettegame.h"

class Application {
public:
	int run();
};

int Application::run() {
	IGame *game = new RouletteGame();
	CrapPlayer player(0);
	player.setGame(game);
	player.play(2);

	return EXIT_SUCCESS;
}

int main() {
	Application app;
	return app.run();
}
