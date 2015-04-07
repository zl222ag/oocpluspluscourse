#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

class Menu {
public:
	Menu();
	int select(int);
	int addMenu(char *);
	int addMenuItem(int, char *);

private:
	static const int MAX_MENU_ITEMS = 100;
	static const int MAX_MENUES = 50;

	struct MenuHolder {
		char *header = NULL;
		char *item[MAX_MENU_ITEMS];
		int length = 0;
	};

	MenuHolder m_menus[MAX_MENUES];
	int m_length = 0;
	void showMenu(int);
};

#endif // MENU_H
