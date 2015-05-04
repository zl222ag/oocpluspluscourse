#ifndef MENU_CPP
#define MENU_CPP

#include <iostream>
#include <limits>
#include <menu.h>
#include <inputoutput.h>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

/* Shows the menu.
 * Returns -1 on error.
 */
int Menu::showMenu(int a_menu) const {
	if (a_menu < 0 || a_menu >= m_length) {
		return -1; // TODO: THROW EXCEPTION
	}

	MenuHolder currentMenu = m_menus[a_menu];
	cout << currentMenu.header << endl << endl;
	cout << "-------------------------------------" << endl;
	cout << "       Choose an item!" << endl << endl;

	cout << "0) Show menu again." << endl;

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

	MenuHolder currentMenu = m_menus[a_menu];
	if (currentMenu.length < 1) {
		return -1; // TODO: THROW EXCEPTION
	}
	int returnValue;
	showMenu(a_menu);

	do {
		returnValue = -1;
		cout << endl << "Write in a number from 0 - " << currentMenu.length <<
			" and press ENTER: ";
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

#endif // MENU_CPP
