#include <iostream>
#include <cstdlib>
#include <menu.h>
#include <inputoutput.h>
#include "CrapGame.h"
#include "CrapPlayer.h"
#include "roulettegame.h"

using std::locale;

class App {
public:
	App(IPlayer* a_player, IGame* a_game) :
		m_player(a_player), m_game(a_game) {
	}

	int run();

private:
	static const int MENU_CHOICE_REPLAY = 0;
	static const int MENU_CHOICE_AMOUNT_REPLAY = 1;
	static const int MENU_CHOICE_STARTING_MONEY = 2;
	static const int MENU_CHOICE_QUIT = 3;
	static const locale APP_LOCALE /* locale("swedish") */;

	static void readEnter() {
		cout << "Tryck på retur för att fortsätta...";
		InputOutput::readEnter();
		cout << endl;
	}

	IPlayer* m_player;
	IGame*   m_game;

	int m_playTimes = 1;
	int m_startingMoney = 1000;


	void replay() {
		m_player->play(m_playTimes);
		cout << "Efter " << m_player->getBetCount() <<
			" spel har spelaren " << m_player->getMoney() <<
			" kronor kvar!" << endl;
		readEnter();
	}

	void setReplayAmount() {
		getIntegerFromUser("Hur många gånger (min 1)?", 1, m_playTimes);
		cout << "Du kommer att spela " << m_playTimes << " gånger!" <<
			endl;
		readEnter();
	}

	void setMenu(Menu &a_menu) {
		a_menu.addMenu("Gamble++");
		a_menu.addMenuItem(0, "Spela angivet antal omgångar och "
			"presentera resultatet.");
		a_menu.addMenuItem(0, "Bestäm antalet omgångar som ska "
			"spelas i alternativ 1.");
		a_menu.addMenuItem(0, "Bestäm hur mycket pengar spelaren "
			"ska ha från början.");
		a_menu.addMenuItem(0, "Avsluta programmet.");
	}

	void setStartingMoney();
	// Reads a number from the user (repeated until it's not an error).
	void getIntegerFromUser(const char *text, int min, int &value);
};

const locale App::APP_LOCALE = locale("swedish");

int App::run() {
	Menu menu;
	int choice;
	bool continuePlaying = true;

	locale::global(APP_LOCALE);
	cout.imbue(APP_LOCALE);
	cin.imbue(APP_LOCALE);

	m_player->setGame(m_game);
	setMenu(menu);

	while (m_player->getMoney() > 0 && continuePlaying) {
		choice = menu.select(0);

		switch (choice) {
		case MENU_CHOICE_REPLAY:
			replay();
			break;

		case MENU_CHOICE_AMOUNT_REPLAY:
			setReplayAmount();
			break;

		case MENU_CHOICE_STARTING_MONEY:
			setStartingMoney();
			break;

		default: // MENU_CHOICE_QUIT:
			continuePlaying = false;
			break;
		}
	}

	cout << "Hej då! Vi ses nästa gång!" << endl;
	readEnter();

	return EXIT_SUCCESS;
}

void App::setStartingMoney() {
	int amount;

	getIntegerFromUser("Hur många kronor (min 1)?", 1, amount);

	if (m_player != NULL) {
		delete m_player;
	}

	m_player = new CrapPlayer(amount);
	cout << "Du kommer att ha " << m_playTimes << " kr att spela för" <<
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
	// Start with a player that has 1000 Kr
	CrapPlayer *player = new CrapPlayer(1000);
	CrapGame game;
	App app(player, &game);
	return	app.run();
}
