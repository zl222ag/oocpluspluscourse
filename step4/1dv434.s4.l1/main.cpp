// main.cpp
// Datum: 2015-04-12
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa en mediabibliotekshanterare.

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <inputoutput.h>
#include <compare.h>
#include <menu.h>
#ifdef _DEBUG
#include "tester.h"
#endif
#include "mediaregister.h"

using std::cout;
using std::endl;
using std::invalid_argument;

class MediaApplication {
	enum MenuItems {
		LOAD_LIBRARY = 0,
		SAVE_LIBRARY = 1,
		SHOW_LIBRARY = 2,
		SORT_LIBRARY = 3,
		QUIT = 4
	};

	MediaRegister m_register;
	Menu m_menu;

	void initMenus();

	void readEnter() {
		cout << "Press a key to continue...";
		InputOutput::readEnter();
		cout << endl;
	}

public:
	MediaApplication() {
		initMenus();
	}

	int run();
};

void MediaApplication::initMenus() {
	m_menu.addMenu("Media Library++");
	m_menu.addMenuItem(0, "Load library");
	m_menu.addMenuItem(0, "Save library");
	m_menu.addMenuItem(0, "Show library");
	m_menu.addMenuItem(0, "Sort library");
	m_menu.addMenuItem(0, "Quit");
}

int MediaApplication::run() {
	char choice = '\0';

#ifdef _DEBUG
	{

		do {
			cout << "Run test first?: ";
			InputOutput::readChar(choice);
			choice = tolower(choice);
			cout << endl;
		} while (choice != 'n' && choice != 'y');

		if (choice == 'y') {
			Tester tester;
			tester.runTests();
		}
	}
#endif

	do {
		choice = m_menu.select(0);

		switch (choice) {
		case MenuItems::LOAD_LIBRARY:
			try {
				m_register.loadReg();
				cout << "Successfully loaded the register from file." << endl;
			} catch (const invalid_argument &e) {
				cout << "Couldn't load the register from file." << endl;
			}

			readEnter();
			break;

		case MenuItems::SAVE_LIBRARY:
			try {
				m_register.saveReg();
				cout << "Successfully saved the register to file." << endl;
			} catch (const invalid_argument &e) {
				cout << "Couldn't load the register to file." << endl;
			}

			readEnter();
			break;

		case MenuItems::SHOW_LIBRARY:
			m_register.showMedia();
			readEnter();
			break;

		case MenuItems::SORT_LIBRARY:
			m_register.sortMedia();
			cout << "Library was sorted!" << endl;
			readEnter();
			break;

		default:
			if (choice != MenuItems::QUIT) {
				throw invalid_argument("Invalid menu option selected!");
			}
		}
	} while (choice != MenuItems::QUIT);

	return EXIT_SUCCESS;
}

int main() {
	MediaApplication app;
	return app.run();
}
