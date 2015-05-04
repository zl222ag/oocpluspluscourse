#include <iostream>
#include <cstdlib>
#include <menu.h>
#include <inputoutput.h>
#include "CrapGame.h"
#include "CrapPlayer.h"
#include "roulettegame.h"

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

	IPlayer* m_player;
	IGame*   m_game;

	int m_playTimes = 1;
	int m_startingMoney = 1000;

	void replay();
	// Reads a number from the user (repeated until it's not an error).
	void App::getIntegerFromUser(const char *text, int min, int &value);
};

int App::run() {
	Menu menu;
	int choice;
	m_player->setGame(m_game);
	menu.addMenu("Gamble++");
	menu.addMenuItem(0, "Spela angivet antal omgångar och "
		"presentera resultatet.");
	menu.addMenuItem(0, "Bestäm antalet omgångar som ska "
		"spelas i alternativ 1.");
	menu.addMenuItem(0, "Bestäm hur mycket pengar spelaren "
		"ska ha från början.");
	menu.addMenuItem(0, "Avsluta programmet.");

	while (m_player->getMoney() > 0) {
		choice = menu.select(0);

		switch (choice) {
		case MENU_CHOICE_REPLAY:
			replay();
			break;

		case MENU_CHOICE_AMOUNT_REPLAY:
			getIntegerFromUser("Hur många gånger (min 1)?", 1, m_playTimes);
			cout << "Du kommer att spela " << m_playTimes << " gånger!" <<
				endl;
			break;

		case MENU_CHOICE_STARTING_MONEY:
			getIntegerFromUser("Hur många kronor (min 1)?", 1, choice);
			cout << "Du kommer att ha " << m_playTimes << " kr att spela för" <<
				endl;

			if (m_player != NULL) {
				delete m_player;
			}

			m_player = new CrapPlayer(choice);
			break;

		default: // MENU_CHOICE_QUIT:
			cout << "Hej då! Vi ses nästa gång!" << endl;
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}

void App::replay() {
	m_player->play(m_playTimes);
	cout << "Efter " << m_player->getBetCount() <<
		" spel har spelaren " << m_player->getMoney() <<
		" kronor kvar!" << endl;
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
	CrapPlayer player(1000); // Start with a player that has 1000 Kr
	CrapGame game;
	App app(&player, &game);
	return	app.run();
}
