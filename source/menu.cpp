#ifndef MENU_CPP
#define MENU_CPP

#include <menu.h>

Menu::Menu() {

}

int Menu::select(int a_menu) {
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (returnValue == 0) {
			cout << endl;
			showMenu(a_menu);
		}
	} while (returnValue < 1 || returnValue > currentMenu.length);

	cout << endl;

	return --returnValue;
}

int Menu::addMenu(char *a_header) {
	if (m_length >= MAX_MENUES) {
		return -1;
	}

	m_menus[m_length].header = a_header;
	return m_length++;
}

int Menu::addMenuItem(int a_menu, char *a_itemText) {
	if (a_menu < 0 || a_menu >= m_length) {
		return -1; // TODO: THROW EXCEPTION
	}
	if (m_menus[a_menu].length >= MAX_MENU_ITEMS) {
		return -1;
	}

	m_menus[a_menu].item[m_menus[a_menu].length] = a_itemText;
	return m_menus[a_menu].length++;
}

void Menu::showMenu(int a_menu) {
	MenuHolder currentMenu = m_menus[a_menu];
	cout << currentMenu.header << endl << endl;
	cout << "-------------------------------------" << endl;
	cout << "       Choose an item!" << endl << endl;

	cout << "0) Show menu again." << endl;

	for (int i = 0; i < currentMenu.length; ++i) {
		cout << i + 1 << ") " << currentMenu.item[i] << endl;
	}
}

#endif // MENU_CPP
