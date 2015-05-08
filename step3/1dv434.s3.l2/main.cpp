#include <iostream>
#include <cstdlib>
#include <menu.h>
#include <inputoutput.h>
#include "CrapGame.h"
#include "CrapPlayer.h"
#include "roulettegame.h"
#include "rouletteplayer.h"
#include "wrapper.h"

#if defined(_WIN32) || defined(_WIN64)
#define _WINDOWS
#endif

using std::locale;

namespace Main {
	enum Menu {
		CRAPS = 0,
		RUSSIAN_ROULETTE = 1,
		QUIT = 2
	};
}

namespace Craps {
	enum Menu {
		REPLAY = 0,
		AMOUNT_REPLAY = 1,
		STARTING_MONEY = 2,
		QUIT = 3
	};
}

namespace RussianRoulette {
	enum Menu {
		SHOOT = 0,
		RELOAD = 1,
		STARTING_MONEY = 2,
		QUIT = 3
	};
}

namespace {
	enum MenuType {
		MAIN = 0,
		CRAPS = 1,
		RUSSIAN_ROULETTE = 2
	};
}

class App {
public:
	App() : m_player(NULL), m_game(NULL) {}

	~App() {
		if (m_game != NULL) {
			delete m_game;
		}

		if (m_player != NULL) {
			delete m_game;
		}
	}

	int run();

private:
	enum GameType {
		CRAPS,
		RUSSIAN_ROULETTE
	};

	static const locale APP_LOCALE /* locale("swedish") ||
	 locale("sv_SE.UTF-8")*/;

	static void readEnter() {
		cout << "Tryck p� retur f�r att forts�tta...";
		InputOutput::readEnter();
		cout << endl;
	}

	IPlayer *m_player;
	IGame *m_game;
	Menu m_menu;

	int m_playTimes = 1;

	void replay() {
		m_player->play(m_playTimes);
		cout << "Efter " << m_player->getBetCount() <<
			" spel har spelaren " << m_player->getMoney() <<
			" kronor kvar!" << endl;
		readEnter();
	}

	void setReplayAmount() {
		getIntegerFromUser("Hur m�nga g�nger (min 1)?", 1, m_playTimes);
		cout << "Du kommer att spela " << m_playTimes << " g�nger!" <<
			endl;
		readEnter();
	}

	void playCraps();
	void playRussianRoulette();
	void buildMenu();
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
	int choice;
	bool continuePlaying = true;

	locale::global(APP_LOCALE);
	cout.imbue(APP_LOCALE);
	cin.imbue(APP_LOCALE);

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

		default:// Main::Menu::CRAPS:
			continuePlaying = false;
			break;
		}
	}

	cout << "Hej d�! Vi ses n�sta g�ng!" << endl;
	readEnter();

	return EXIT_SUCCESS;
}

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
				cout << "Du m�ste v�lja alternativ 3. f�rst!" << endl;
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
			cout << "Verkar som att du f�rlorade!" << endl;
			readEnter();
		}
	}
}

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
				cout << "Du m�ste v�lja alternativ 3. f�rst!" << endl;
				readEnter();
				break;
			}

			m_player->play(0);

			if (m_player->getMoney() <= 0) {
				delete m_player;
				m_player = NULL;
				cout << "Verkar som att du dog!" << endl <<
					"V�lj summa f�r att b�rja om" << endl;
			} else {
				cout << "Du lever fortfarande och du har nu " <<
					m_player->getMoney() << " kr!" << endl <<
					"Du har klarat dig i " << m_player->getBetCount() <<
					" rundor!" << endl;
			}
			readEnter();
			break;

		case RussianRoulette::Menu::RELOAD:
			if (m_player == NULL) {
				cout << "Du m�ste v�lja alternativ 3. f�rst!" << endl;
				readEnter();
				break;
			}

			m_player->play(1);

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

void App::buildMenu() {
	m_menu.addMenu("Gamble++: V�lj spel! Eller avsluta?");
	m_menu.addMenuItem(MenuType::MAIN, "Craps.");
	m_menu.addMenuItem(MenuType::MAIN, "Rysk roulette.");
	m_menu.addMenuItem(MenuType::MAIN, "Avsluta programmet.");

	m_menu.addMenu("Craps");
	m_menu.addMenuItem(MenuType::CRAPS, "Spela angivet antal omg�ngar och "
		"presentera resultatet.");
	m_menu.addMenuItem(MenuType::CRAPS, "Best�m antalet omg�ngar som ska "
		"spelas i alternativ 1.");
	m_menu.addMenuItem(MenuType::CRAPS, "Best�m hur mycket pengar spelaren "
		"ska ha fr�n b�rjan.");
	m_menu.addMenuItem(MenuType::CRAPS, "Avsluta spelet.");

	m_menu.addMenu("Rysk roulette");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Skjut");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Ladda om");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Best�m hur mycket pengar spelaren "
		"ska ha fr�n b�rjan.");
	m_menu.addMenuItem(MenuType::RUSSIAN_ROULETTE, "Avsluta spelet.");
}

void App::setStartingMoney(GameType a_type) {
	int amount;

	getIntegerFromUser("Hur m�nga kronor (min 1)?", 1, amount);

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

	cout << "Du kommer att ha " << amount << " kr att spela f�r" <<
		endl;

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
