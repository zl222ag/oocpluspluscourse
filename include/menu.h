#ifndef MENU_H
#define MENU_H

#include <locale>

class Menu {
	static const int MAX_MENU_ITEMS = 100;
	static const int MAX_MENUES = 50;
	static const std::locale SWEDISH_LOCALE /* locale("swedish") ||
	 locale("sv_SE.UTF-8")*/;

	struct MenuHolder {
		const char *header = NULL;
		const char *item[MAX_MENU_ITEMS];
		int length = 0;
	};

	MenuHolder m_menus[MAX_MENUES];
	int m_length = 0;

	/* Shows the menu.
	 * Returns -1 on error.
	 */
	int showMenu(int menu) const;
public:
	Menu() {}

	/* Shows a selected menu.
	 * Reads cin from user and returns item.
	 * Returns -1 on error.
	 */
	int select(int menu) const;
	/* Adds a menu.
	 * returns -1 on error (if it reached the limit).
	 */
	int addMenu(const char *header);
	/* Adds a menu item to an existing menu.
	 * Returns -1 on error.
	 */
	int addMenuItem(int menu, const char *itemText);
};

#endif // MENU_H
