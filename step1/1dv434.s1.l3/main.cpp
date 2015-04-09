// 1dv434.s1.l3/main.cpp
// Datum: 2015-04-07
// Programmerare: Zlatko Ladan
// Kort beskrivning: Skapa program som fungerar med klassen TakeFive.

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <locale>
#include <menu.h>
#include "TakeFive.h"

using std::cout;
using std::cin;
using std::locale;
using std::runtime_error;

class App {
public:
    // Runnin'
	int run();

private:
	enum StartingPlayer {
		NONE,
		PLAYER,
		COMPUTER
	};

	static const int MAIN_MENU = 0;
	static const int STARTER_MENU = 1;
	static const int OBJECT_MENU = 2;

	static const int STARTER_MENU_ITEM = 0;
	static const int OBJECT_CHOICE_MENU_ITEM = 1;
	static const int BOARD_SIZE_MENU_ITEM = 2;
	static const int START_GAME_MENU_ITEM = 3;
	static const int CLOSE_GAME_MENU_ITEM = 4;

	static const int STARTER_PLAYER_MENU_ITEM = 0;
	static const int STARTER_COMPUTER_MENU_ITEM = 1;

	static const int OBJECT_CROSS_MENU_ITEM = 0;
	static const int OBJECT_RING_MENU_ITEM = 1;

	static const int MIN_COLUMNS = 5;
	static const int MAX_COLUMNS = 55;
	static const int MIN_ROWS = 5;
	static const int MAX_ROWS = 75;

	Menu m_menu;
	TakeFive *m_board = NULL;
	Player m_humanPlayer = Player::NONE, m_computerPlayer = Player::NONE;

	// Reads a number from the user (repeated until it's not an error).
	// With min and max.
	static void getIntegerFromUser(char *, int &, int, int);

	// Reads a number from the user (repeated until it's not an error).
	static void getIntegerFromUser(char *, int &);

	// Reads a single character from user (repeated until it's not an error).
	static void getCharacterFromUser(char *, char &);

	// Ignores input until a new line, or enter
	static void readEnter();

	// Creates the menus that are used
	void loadMenus();

	// Sets the users object to play with, also the computers (opposite).
	void setPlayerObject(Player);

	// Easy method that asks the user for input.
	Player playerMakeMove();
};

// Runnin'
int App::run() {
	//	setLanguage();
	StartingPlayer startingPlayer = StartingPlayer::NONE;
	bool startGame = false;
	char doContinue = '\0';

	srand((unsigned int) time(NULL)); // randomizes with time

	loadMenus();

	do {
		startGame = false;

		do {
			switch (m_menu.select(MAIN_MENU)) {
			case STARTER_MENU_ITEM:
				if (m_menu.select(STARTER_MENU) == STARTER_PLAYER_MENU_ITEM) {
					startingPlayer = StartingPlayer::PLAYER;
					cout << "You are ";
				} else {
					startingPlayer = StartingPlayer::COMPUTER;
					cout << "The computer is ";
				}
				cout << "going to start first.";

				readEnter();
				cout << endl;
				break;

			case OBJECT_CHOICE_MENU_ITEM:
				if (m_menu.select(OBJECT_MENU) == OBJECT_CROSS_MENU_ITEM) {
					setPlayerObject(Player::CROSS);

					cout << "You choose to play as \"X\"";
				} else {
					setPlayerObject(Player::RING);

					cout << "You choose to play as \"O\"";
				}

				readEnter();
				cout << endl;
				break;

			case BOARD_SIZE_MENU_ITEM:
				int cols, rows;
				getIntegerFromUser("Enter number of columns for the field",
					cols, MIN_COLUMNS, MAX_COLUMNS);
				getIntegerFromUser("Enter number of rows for the field",
					rows, MIN_COLUMNS, MAX_ROWS);

				if (m_board != NULL) {
					delete m_board;
				}
				m_board = new TakeFive(cols, rows);

				readEnter();
				break;

			case START_GAME_MENU_ITEM:
				if (m_board == NULL) {
					cout << "Error, field size should be set first!";
					readEnter();
					cout << endl;
				} else {
					startGame = true;
					m_board->startNewGame();
				}
				break;

			case CLOSE_GAME_MENU_ITEM:
				return EXIT_SUCCESS;
			}
		} while (m_board == NULL || !startGame);

		if (m_humanPlayer == Player::NONE) {
			setPlayerObject((((rand() % 100) < 50) ?
				Player::CROSS : Player::RING));
		}

		if (startingPlayer == StartingPlayer::NONE) {
			startingPlayer = (((rand() % 100) < 50) ?
				StartingPlayer::PLAYER : StartingPlayer::COMPUTER);
		}

		Player result = Player::NONE;
		if (startingPlayer == StartingPlayer::PLAYER) {
			m_board->show();
		}

		while (m_board->gameIsActive() && result == Player::NONE) {
			if (startingPlayer == StartingPlayer::PLAYER) {
				result = playerMakeMove();
				if (result == Player::NONE) {
					result = m_board->makeMove(m_computerPlayer);
					m_board->show();
				}
			} else {
				result = m_board->makeMove(m_computerPlayer);
				if (result == Player::NONE) {
					m_board->show();
					result = playerMakeMove();
				}
			}
		}

		m_board->show();
		if (result == Player::ERROR) {
			cout << "Whoops, an error seems to have occurred!" << endl;
		} else {
			if (result == m_humanPlayer) {
				cout << "Congratulations, you won!" << endl;
			} else {
				cout << "Sorry, you lost." << endl;
			}
		}

		do {
			getCharacterFromUser("Continue playing?: ", doContinue);
			doContinue = tolower(doContinue);
		} while (doContinue != 'y' && doContinue != 'n');
	} while ((doContinue == 'y'));

	return EXIT_SUCCESS;
}

// Reads a number from the user (repeated until it's not an error).
// With min and max.
void App::getIntegerFromUser(char *a_text, int &a_value, int a_min, int a_max) {
	if (a_min > a_max) {
		throw runtime_error("Error cannot have a min value "
			"greater than the max value!");
	}
	int temp;
	bool error = false;

	do {
		cout << a_text << " (min: " << a_min << ", max: " << a_max << "): ";
		cin >> temp;
		error = cin.fail();
		cin.clear();
		readEnter();
		cout << endl;
		if (!error) {
			if (temp < a_min) {
				cout << "Too low!" << endl << endl;
			} else if (temp > a_max) {
				cout << "Too high!" << endl << endl;
			}
		}
	} while (error || temp < a_min || temp > a_max);

	a_value = temp;
}

// Reads a number from the user (repeated until it's not an error).
void App::getIntegerFromUser(char *a_text, int &a_value) {
	int temp;
	bool error = false;

	do {
		cout << a_text;
		cin >> temp;
		error = cin.fail();
		cin.clear();
		readEnter();
		cout << endl;
	} while (error);

	a_value = temp;
}

// Reads a single character from user (repeated until it's not an error).
void App::getCharacterFromUser(char *a_text, char &a_value) {
	char temp;
	bool error = false;

	do {
		cout << a_text;
		cin.get(temp);
		error = cin.fail();
		cin.clear();
		readEnter();
		cout << endl;
	} while (error);

	a_value = temp;
}

// Ignores input until a new line, or enter
void App::readEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Creates the menus that are used
void App::loadMenus() {
	m_menu.addMenu("Welcome to a game of noughts and crosses");
	m_menu.addMenuItem(MAIN_MENU, "Choose if you or the computer should start");
	m_menu.addMenuItem(MAIN_MENU, "Choose if you want to be \"X\" or \"O\"");
	m_menu.addMenuItem(MAIN_MENU, "Choose the size of the field");
	m_menu.addMenuItem(MAIN_MENU, "Start the game");
	m_menu.addMenuItem(MAIN_MENU, "Close application");

	m_menu.addMenu("Should you start or the computer?");
	m_menu.addMenuItem(STARTER_MENU, "Me");
	m_menu.addMenuItem(STARTER_MENU, "The Computer");

	m_menu.addMenu("Do you want to be \"X\" or \"O\"?");
	m_menu.addMenuItem(OBJECT_MENU, "X");
	m_menu.addMenuItem(OBJECT_MENU, "O");
}

// Sets the users object to play with, also the computers (opposite).
void App::setPlayerObject(Player a_object) {
	if (a_object == Player::CROSS) {
		m_humanPlayer = Player::CROSS;
		m_computerPlayer = Player::RING;
		return;
	}

	m_humanPlayer = Player::RING;
	m_computerPlayer = Player::CROSS;
}

// Easy method that asks the user for input.
Player App::playerMakeMove() {
	int val = 0;
	char chr = '\0';
	Player returnValue = Player::NONE;

	do {
		getCharacterFromUser("Choose column: ", chr);
		getIntegerFromUser("Choose row: ", val);

		returnValue = m_board->makeMove(m_humanPlayer, val, chr);
	} while (returnValue == Player::ERROR);
	return Player::NONE;
}

// Starts here.
int main() {
	App app;

	return app.run();
}
