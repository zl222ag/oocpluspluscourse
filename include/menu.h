#ifndef MENU_H
#define MENU_H

#include <cstdlib>

class Menu {
public:
	Menu();
	int select(int) const;
	int addMenu(const char *);
	int addMenuItem(int, const char *);

private:
	static const int MAX_MENU_ITEMS = 100;
	static const int MAX_MENUES = 50;

	struct MenuHolder {
		const char *header = NULL;
		const char *item[MAX_MENU_ITEMS];
		int length = 0;
	};

	MenuHolder m_menus[MAX_MENUES];
	int m_length = 0;
	void showMenu(int) const;
};

#endif // MENU_H
