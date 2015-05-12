// 1dv434.s3.l2/main.cpp
// Datum: 2015-05-03
// Programmerare: Zlatko Ladan
// Kort beskrivning: Skapa program som utnyttjar polymorfism och där man kan
// spela hasardspel.
#include <iostream>
#include <cstdlib>
#include <menu.h>
#include <inputoutput.h>
#ifdef _DEBUG
#include <cassert>
#endif
#include "CrapGame.h"
#include "CrapPlayer.h"
#include "roulettegame.h"
#include "rouletteplayer.h"
#include "wrapper.h"

#if defined(_WIN32) || defined(_WIN64)
#define _WINDOWS
#endif

using std::locale;

// namespaces are necessary since there are similar names!
namespace Main {
enum Menu {
	CRAPS = 0, RUSSIAN_ROULETTE = 1, QUIT = 2
};
}

namespace Craps {
enum Menu {
	REPLAY = 0, AMOUNT_REPLAY = 1, STARTING_MONEY = 2, QUIT = 3
};
}

namespace RussianRoulette {
enum Menu {
	SHOOT = 0, RELOAD = 1, STARTING_MONEY = 2, QUIT = 3
};
}

namespace {
enum MenuType {
	MAIN = 0, CRAPS = 1, RUSSIAN_ROULETTE = 2
};
}

class App {
public:
	App() :
			m_player(NULL), m_game(NULL) {
	}

	~App() {
		if (m_game != NULL) {
			delete m_game;
		}

		if (m_player != NULL) {
			delete m_player;
		}
	}

	int run();

#ifdef _DEBUG
	void testCode();
#endif

private:
	enum GameType {
		CRAPS, RUSSIAN_ROULETTE
	};

	static const locale APP_LOCALE /* locale("swedish") ||
	 locale("sv_SE.UTF-8")*/;

	// Writes a message and requires the user to input enter.
	static void readEnter() {
		cout << "Tryck på retur för att fortsätta...";
		InputOutput::readEnter();
		cout << endl;
	}

	IPlayer *m_player;
	IGame *m_game;
	Menu m_menu;

	int m_playTimes = 1;

	// "Plays" the actual game of craps.
	void replay() {
		m_player->play(m_playTimes);
		cout << "Efter " << m_player->getBetCount() << " spel har spelaren "
				<< m_player->getMoney() << " kronor kvar!" << endl;
		readEnter();
	}

	// Asks the user for times for replay
	void setReplayAmount() {
		getIntegerFromUser("Hur många gånger (min 1)? ", 1, m_playTimes);
		cout << "Du kommer att spela " << m_playTimes << " gånger!" << endl;
		readEnter();
	}

	// Starts the craps game
	void playCraps();
	// Starts the russian roulette game
	void playRussianRoulette();
	// Builds the menus for the selection of games and for the games: russian
	// roulette, and craps.
	void buildMenu();
	// Sets the starting money for the selected game
	void setStartingMoney(GameType);
	// Reads a number from the user (repeated until it's not an error).
	static void getIntegerFromUser(const char *text, int min, int &value);
};

#ifdef _WINDOWS
const locale App::APP_LOCALE = locale("swedish");
#else
const locale App::APP_LOCALE = locale("sv_SE.UTF-8");
#endif

int App::run() {
	locale::global(APP_LOCALE);
	cout.imbue(APP_LOCALE);
	cin.imbue(APP_LOCALE);

#ifdef _DEBUG
	{
		char chr = 'n';

		do {
			cout << "Testa koden istället för att köra spelet? ";
			InputOutput::readChar(chr);
			chr = tolower(chr);
		} while (chr != 'j' && chr != 'n');

		if (chr == 'j') {
			testCode();
			return EXIT_SUCCESS;
		}
	}
#endif

	int choice;
	bool continuePlaying = true;

	buildMenu();

	while (continuePlaying) {
		choice = m_menu.select(MenuType::MAIN);

		switch (choice) {
		case Main::Menu::CRAPS:
			playCraps();
			break;

		case Main::Menu::RUSSIAN_ROULETTE:
			playRussianRoulette();
			break;

		default:	// Main::Menu::CRAPS:
			continuePlaying = false;
			break;
		}
	}

	cout << "Hej då! Vi ses nästa gång!" << endl;
	readEnter();

	return EXIT_SUCCESS;
}

#ifdef _DEBUG
void App::testCode() {
	const int GAME_PLAY_LOOPS = 100;
	int loops, res;
	bool allLoopsEq1 = true;
	m_game = new RouletteGame();

	cout << "Testar Roulette game revolver (" << GAME_PLAY_LOOPS
			<< " gånger), 6 kammare i detta fallet!" << endl;

	cout << "Iterationer: " << endl;

	for (int i = 0; i < GAME_PLAY_LOOPS; ++i) {
		loops = 0;

		do {
			res = m_game->play("shoot", 100);
			++loops;
		} while (res != 0);

		cout << " " << loops;

		if (allLoopsEq1 && loops != 1) {
			allLoopsEq1 = false;
		}

		if (i % 10 == 9) {
			cout << endl;
		}

		assert(loops <= 6);
	}

	assert(!allLoopsEq1);
	cout << endl;

	cout << "Testar Roulette game, skjuter och laddar (NULL med) "
			"med negativa och ingen summa pengar!" << endl;

	assert(m_game->play("shoot", 0) == 0);
	assert(m_game->play("shoot", -100) == 0);
	assert(m_game->play("reload", 0) == 0);
	assert(m_game->play("reload", -1234) == 0);
	assert(m_game->play(NULL, 0) == 0);

	cout << endl;

	m_player = new RoulettePlayer(10);
	assert(m_player->getMoney() == 10);

	cout << "Testar Roulette player, kan hen spela Roulette? (ja)" << endl;
	assert(m_player->setGame(m_game));

	cout << "Testar Roulette player, kan hen ladda om? (ja)" << endl;
	assert(m_player->play(RoulettePlayer::RouletteChoice::RELOAD));

	cout << "Testar Roulette player, kan hen skjuta? (ja)" << endl;
	assert(m_player->play(RoulettePlayer::RouletteChoice::SHOOT));

	loops = 1;

	while (m_player->getMoney() > 0 && loops <= 6) {
		assert(m_player->play(RoulettePlayer::RouletteChoice::SHOOT));
		++loops;
	}

	cout << "Testar Roulette player, kan hen ha skjutit mindre än 7 gånger? "
			"(ja)" << endl;
	assert(loops <= 6);

	cout << "Testar Roulette player, är antalet satsningar (betCount) "
			"lika med antalet iterationer? (ja)" << endl;
	assert(loops == m_player->getBetCount());

	delete m_player;
	m_player = new CrapPlayer(1000);

	cout << endl;
	cout << "Testar Craps player, kan hen spela Roulette? (nej)" << endl;
	assert(!m_player->setGame(m_game));

	delete m_game;
	m_game = new Wrapper();

	cout << "Testar Craps player, kan hen spela Craps? (ja)" << endl;
	assert(m_player->setGame(m_game));

	cout << "Testar Craps player, spelat noll gånger? (ja)" << endl;
	assert(m_player->getBetCount() == 0);

	cout << "Testar Craps player, om hen förlorar, får spelaren då behålla "
			"pengarna och borde antalet iterationer vara samma som antalet "
			"satsningar (betCount)? (nej, ja)" << endl;
	loops = 0;

	while (m_player->getMoney() > 0) {
		if (!m_player->play(10)) {
			assert(m_player->getMoney() == 0);
			break;
		}

		loops += 10;
		assert(m_player->getBetCount() == loops);
	}

	cout << "Spelaren spelade " << loops << " rundor (om det heter så)."
			<< endl;
}
#endif

// Starts the craps game
void App::playCraps() {
	bool continuePlaying = true;
	int choice;

	if (m_player != NULL) {
		delete m_player;
		m_player = NULL;
	}

	if (m_game != NULL) {
		delete m_game;
	}

	m_game = new Wrapper();

	while (continuePlaying) {
		choice = m_menu.select(MenuType::CRAPS);

		switch (choice) {
		case Craps::Menu::REPLAY:
			if (m_player == NULL) {
				cout << "Du måste välja alternativ 3. först!" << endl;
				readEnter();
				break;
			}

			replay();
			break;

		case Craps::Menu::AMOUNT_REPLAY:
			setReplayAmount();
			break;

		case Craps::Menu::STARTING_MONEY:
			setStartingMoney(GameType::CRAPS);
			break;

		default: // Craps::Menu::QUIT:
			continuePlaying = false;
			break;
		}

		if (m_player != NULL && m_player->getMoney() <= 0) {
			delete m_player;
			m_player = NULL;
			cout << "Verkar som att spelaren förlorade!" << endl;
			readEnter();
		}
	}
}

// Starts the russian roulette game
void App::playRussianRoulette() {
	bool continuePlaying = true;
	int choice;

	if (m_player != NULL) {
		delete m_player;
		m_player = NULL;
	}

	if (m_game != NULL) {
		delete m_game;
	}

	m_game = new RouletteGame();

	while (continuePlaying) {
		choice = m_menu.select(MenuType::RUSSIAN_ROULETTE);

		switch (choice) {
		case RussianRoulette::Menu::SHOOT:
			if (m_player == NULL) {
				cout << "Du måste välja alternativ 3. först!" << endl;
				readEnter();
				break;
			}

			m_player->play(RoulettePlayer::RouletteChoice::SHOOT);

			if (m_player->getMoney() <= 0) {
				delete m_player;
				m_player = NULL;
				cout << "Verkar som att spelaren dog!" << endl
						<< "Välj summa för att börja om" << endl;
			} else {
				cout << "Du lever fortfarande och spelaren har nu "
						<< m_player->getMoney() << " kr!" << endl
						<< "Du har klarat dig i " << m_player->getBetCount()
						<< " rundor!" << endl;
			}
			readEnter();
			break;

		case RussianRoulette::Menu::RELOAD:
			if (m_player == NULL) {
				cout << "Du måste välja alternativ 3. först!" << endl;
				readEnter();
				break;
			}

			m_player->play(RoulettePlayer::RouletteChoice::RELOAD);

			cout << "Snurrade magasinet!" << endl;
			readEnter();
			break;

		case RussianRoulette::Menu::STARTING_MONEY:
			setStartingMoney(GameType::RUSSIAN_ROULETTE);
			break;

		default: // RussianRoulette::Menu::QUIT:
			continuePlaying = false;
			break;
		}
	}
}

// Builds the menus for the selection of games and for the games: russian
// roulette, and craps.
void App::buildMenu() {
	m_menu.addMenu("Gamble++: Välj spel! Eller avsluta?");
	m_menu.addMenuItem(MenuType::MAIN, "Craps.");
	m_menu.addMenuItem(MenuType::MAIN, "Rysk roulette.");
	m_menu.addMenuItem(MenuType::MAIN, "Avsluta programmet.");

	m_menu.addMenu("Craps");
	m_menu.addMenuItem(MenuType::CRAPS, "Spela angivet antal omgångar och "
			"presentera resultatet.");
	m_menu.addMenuItem(MenuType::CRAPS, "Bestäm antalet omgångar som ska "
			"spelas i alternativ 1.");
	m_menu.addMenuItem(MenuType::CRAPS, "Bestäm hur mycket pengar spelaren "
			"ska ha från början.");
	m_menu.addMenuItem(MenuType::CRAPS, "Avsluta spelet.");

	m_menu.addMenu("Rysk roulette");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Skjut");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Ladda om");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE,
			"Bestäm hur mycket pengar spelaren "
					"ska ha från början.");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Avsluta spelet.");
}

// Sets the starting money for the selected game
void App::setStartingMoney(GameType a_type) {
	int amount;

	getIntegerFromUser("Hur många kronor (min 1)? ", 1, amount);

	if (m_player != NULL) {
		delete m_player;
	}

	if (a_type == GameType::CRAPS) {
		m_player = new CrapPlayer(amount);
		m_player->setGame(m_game);
	} else { // GameType::RUSSIAN_ROULETTE
		m_player = new RoulettePlayer(amount);
		m_player->setGame(m_game);
	}

	cout << "Du kommer att ha " << amount << " kr att spela för" << endl;

	readEnter();
}

// Reads a number from the user (repeated until it's not an error).
void App::getIntegerFromUser(const char *a_text, int a_min, int &a_value) {
	int temp;
	bool error = false;

	do {
		cout << a_text;
		cin >> temp;
		error = cin.fail();
		cin.clear();
		InputOutput::readEnter();
		cout << endl;
	} while (error || temp < a_min);

	a_value = temp;
}

int main() {
	App app;
	return app.run();
}
