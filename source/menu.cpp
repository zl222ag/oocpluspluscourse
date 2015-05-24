#include <iostream>
#include <limits>
#include <menu.h>
#include <inputoutput.h>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::locale;

#if defined(_WIN32) || defined(_WIN64)
#define _WINDOWS
#endif

#ifdef _WINDOWS
const locale Menu::SWEDISH_LOCALE = locale("swedish");
#else
const locale Menu::SWEDISH_LOCALE = locale("sv_SE.UTF-8");
#endif

/* Shows the menu.
 * Returns -1 on error.
 */
int Menu::showMenu(int a_menu) const {
	if (a_menu < 0 || a_menu >= m_length) {
		return -1; // TODO: THROW EXCEPTION
	}

	bool swedish = cout.getloc() == SWEDISH_LOCALE;
	MenuHolder currentMenu = m_menus[a_menu];

	cout << currentMenu.header << endl << endl;
	cout << "-------------------------------------" << endl;
	if (swedish) {
		cout << "     Välj ett alternativ!" << endl << endl;
		cout << "0) Visa menyn igen." << endl;
	} else {
		cout << "       Choose an item!" << endl << endl;
		cout << "0) Show menu again." << endl;
	}

	for (int i = 0; i < currentMenu.length; ++i) {
		cout << i + 1 << ") " << currentMenu.item[i] << endl;
	}

	return 0;
}

/* Shows a selected menu.
 * Reads cin from user and returns item.
 * Returns -1 on error.
 */
int Menu::select(int a_menu) const {
	if (a_menu < 0 || a_menu >= m_length) {
		return -1; // TODO: THROW EXCEPTION
	}

	bool swedish = cout.getloc() == SWEDISH_LOCALE;
	MenuHolder currentMenu = m_menus[a_menu];

	if (currentMenu.length < 1) {
		return -1; // TODO: THROW EXCEPTION
	}

	int returnValue;
	showMenu(a_menu);

	do {
		returnValue = -1;
		if (swedish) {
			cout << endl << "Skriv in ett nummer från 0 - " <<
				currentMenu.length << " och tryck sedan på RETUR: ";
		} else {
			cout << endl << "Write in a number from 0 - " <<
				currentMenu.length << " and press ENTER: ";
		}
		cin >> returnValue;
		cin.clear();
		InputOutput::readEnter();

		if (returnValue == 0) {
			cout << endl;
			showMenu(a_menu);
		}
	} while (returnValue < 1 || returnValue > currentMenu.length);

	cout << endl;

	return --returnValue;
}

/* Adds a menu.
 * returns -1 on error (if it reached the limit).
 */
int Menu::addMenu(const char *a_header) {
	if (m_length >= MAX_MENUES) {
		return -1;
	}

	m_menus[m_length].header = a_header;
	return m_length++;
}

/* Adds a menu item to an existing menu.
 * Returns -1 on error.
 */
int Menu::addMenuItem(int a_menu, const char *a_itemText) {
	if (a_menu < 0 || a_menu >= m_length) {
		return -1; // TODO: THROW EXCEPTION
	}
	if (m_menus[a_menu].length >= MAX_MENU_ITEMS) {
		return -1;
	}

	m_menus[a_menu].item[m_menus[a_menu].length] = a_itemText;
	return m_menus[a_menu].length++;
}
