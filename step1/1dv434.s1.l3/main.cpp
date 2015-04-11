// 1dv434.s1.l3/main.cpp
// Datum: 2015-04-07
// Programmerare: Zlatko Ladan
// Kort beskrivning: Skapa program som fungerar med klassen TakeFive.

#include <cstdlib>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <locale>
#include <menu.h>
#include "TakeFive.h"

using std::cout;
using std::cin;
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
	Player m_humanPlayer = Player::NONE, m_computerPlayer = Player::NONE;

	// Reads a number from the user (repeated until it's not an error).
	// With min and max.
	static void getIntegerFromUser(const char *, int &, int, int);

	// Reads a number from the user (repeated until it's not an error).
	static void getIntegerFromUser(const char *, int &);

	// Reads a single character from user (repeated until it's not an error).
	static void getCharacterFromUser(const char *, char &);

	// Ignores input until a new line, or enter.
	static void readEnter();

	// Returns a random boolean value (true, or false).
	static bool randomBool();

	// Start the actual game.
	void playGame(StartingPlayer, int, int);

	// Creates the menus that are used.
	void loadMenus();

	// Sets the users object to play with, also the computers (opposite).
	void setPlayerObject(Player);

	// Easy method that asks the user for input.
	Player playerMakeMove(TakeFive &);
};

// Runnin'
int App::run() {
	// setLanguage();
	StartingPlayer startingPlayer = StartingPlayer::NONE;
	bool startGame = false;
	char doContinue = '\0';
	int cols, rows;

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
				getIntegerFromUser("Enter number of columns for the field",
					cols, MIN_COLUMNS, MAX_COLUMNS);
				getIntegerFromUser("Enter number of rows for the field",
					rows, MIN_COLUMNS, MAX_ROWS);

				cout << "Number of columns: " << cols << ", number of rows: " <<
						rows;

				readEnter();
				cout << endl;
				break;

			case START_GAME_MENU_ITEM:
				if (cols < 1 || rows < 1) {
					cout << "Error, field size should be set first!";
					readEnter();
					cout << endl;
				} else {
					startGame = true;
				}
				break;

			case CLOSE_GAME_MENU_ITEM:
				return EXIT_SUCCESS;
			}
		} while (!startGame);

		if (m_humanPlayer == Player::NONE) {
			setPlayerObject((randomBool() ?
				Player::CROSS : Player::RING));
		}
		cout << "You are going to play as \"" <<
			((m_humanPlayer == Player::CROSS) ? 'X' : 'O') << "\"." << endl;

		if (startingPlayer == StartingPlayer::NONE) {
			startingPlayer = (randomBool() ?
				StartingPlayer::PLAYER : StartingPlayer::COMPUTER);
		}

		playGame(startingPlayer, cols, rows);

		do {
			getCharacterFromUser("Restart form menu?: ", doContinue);
			doContinue = tolower(doContinue);
		} while (doContinue != 'y' && doContinue != 'n');
	} while (doContinue == 'y');

	return EXIT_SUCCESS;
}

// Start the actual game.
void App::playGame(StartingPlayer startingPlayer, int a_cols, int a_rows) {
	if (startingPlayer == StartingPlayer::NONE) {
		throw runtime_error("Starting player cannot be \"NONE\"!");
	}
	if (a_cols < MIN_COLUMNS || a_rows < MIN_ROWS || a_cols > MAX_COLUMNS ||
			a_rows > MAX_ROWS) {
		throw runtime_error("Columns nor rows follow the conditions!");
	}
	TakeFive board(a_rows, a_cols);
	Player result = Player::NONE;

	unsigned int i = 0;
	while (board.gameIsActive() && result == Player::NONE &&
			((signed) i) < (a_cols * a_rows)) {
		board.show();

		if ((i % 2 == 0 && startingPlayer == StartingPlayer::COMPUTER) ||
				(i % 2 == 1 && startingPlayer == StartingPlayer::PLAYER)) {
			result = board.makeMove(m_computerPlayer);
		} else {
			result = playerMakeMove(board);
		}
		++i;
	}

	board.show();

	// No switch here, "impossible".
	if (result == Player::ERROR) {
		cout << "Whoops, an error seems to have occurred!" << endl;
	} else if (result == m_humanPlayer) {
		cout << "Congratulations, you won!" << endl;
	} else if (result == m_computerPlayer) {
		cout << "Sorry, you lost." << endl;
	} else {
		cout << "Nobody won" << endl;
	}
}

// Reads a number from the user (repeated until it's not an error).
// With min and max.
void App::getIntegerFromUser(const char *a_text, int &a_value, int a_min,
		int a_max) {
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
void App::getIntegerFromUser(const char *a_text, int &a_value) {
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
void App::getCharacterFromUser(const char *a_text, char &a_value) {
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

// Returns a random boolean value (true, or false).
bool App::randomBool() {
	return ((rand() % 100) < 50);
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
Player App::playerMakeMove(TakeFive &a_board) {
	int val = 0;
	char chr = '\0';
	Player returnValue = Player::NONE;

	do {
		if (returnValue == Player::ERROR) {
			cout << "INVALID position, try again!" << endl;
			a_board.show();
		}
		getCharacterFromUser("Choose column: ", chr);
		getIntegerFromUser("Choose row: ", val);

		returnValue = a_board.makeMove(m_humanPlayer, val, chr);
	} while (returnValue == Player::ERROR);
	return returnValue;
}

// Starts here.
int main() {
	App app;

	return app.run();
}
