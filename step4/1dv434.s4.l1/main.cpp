// main.cpp
// Datum: 2015-04-12
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa en mediabibliotekshanterare.

#include <cstdlib>
#include <iostream>
#include <vector>
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

namespace Main {
enum MenuItems {
	LOAD_LIBRARY = 0,
	SAVE_LIBRARY = 1,
	SHOW_LIBRARY = 2,
	SORT_LIBRARY = 3,
	ADD_ALBUM = 4,
	MANAGE_ALBUM = 5,
	SHOW_ARTIST_ALBUMS = 6,
	QUIT = 7
};
}

namespace Album {
enum MenuItems {
	SHOW = 0, EDIT = 1, REMOVE = 2, QUIT = 3
};
}

class MediaApplication {
	static void readLine(const char *text, char *out, const size_t size);

	static void readEnter() {
		cout << "Press a key to continue...";
		InputOutput::readEnter();
		cout << endl;
	}

	MediaRegister m_register;
	Menu m_menu;

	void initMenus();
	MusicAlbumMedia createAlbum() throw (invalid_argument);
	void removeAlbum(const MusicAlbumMedia &) throw (runtime_error);
	MusicAlbumMedia *findAlbum();
	void manageAlbum(MusicAlbumMedia album);
	void showArtistAlbums();

public:
	MediaApplication() {
		initMenus();
	}

	int run();
};

void MediaApplication::readLine(const char *a_text, char *a_out,
		const size_t a_size) {
	bool error = false;

	do {
		cout << a_text;
		cin.getline(a_out, a_size);
		error = !cin.good();
		cin.clear();
	} while (error || strlen(a_out) < 1);
}

void MediaApplication::initMenus() {
	m_menu.addMenu("Media Library++");
	m_menu.addMenuItem(0, "Load library");
	m_menu.addMenuItem(0, "Save library");
	m_menu.addMenuItem(0, "Show library");
	m_menu.addMenuItem(0, "Sort library");
	m_menu.addMenuItem(0, "Add album");
	m_menu.addMenuItem(0, "Manage album");
	m_menu.addMenuItem(0, "Show artists album");
	m_menu.addMenuItem(0, "Quit");

	m_menu.addMenu("Album");
	m_menu.addMenuItem(1, "Show");
	m_menu.addMenuItem(1, "Edit");
	m_menu.addMenuItem(1, "Remove");
	m_menu.addMenuItem(1, "Exit this menu");
}

MusicAlbumMedia MediaApplication::createAlbum() throw (invalid_argument) {
	char artistName[MusicAlbumMedia::CHARS_LIMIT];
	char albumName[MusicAlbumMedia::CHARS_LIMIT];
	int releaseYear = 0;

	readLine("Enter the artist's name: ", artistName,
			MusicAlbumMedia::CHARS_LIMIT);
	readLine("Enter the album name: ", albumName, MusicAlbumMedia::CHARS_LIMIT);
	InputOutput::readInteger("Enter the album's release year: ", releaseYear,
			-3000, 3000);

	return MusicAlbumMedia(artistName, albumName, (short) releaseYear);
}

void MediaApplication::removeAlbum(const MusicAlbumMedia &a_album)
		throw (runtime_error) {

	if (!m_register.removeMedia(a_album)) {
		throw runtime_error("Something went wrong when removing the album!");
	}

	cout << "The album " << a_album << " was removed." << endl;
}

MusicAlbumMedia *MediaApplication::findAlbum() {
	char artistName[MusicAlbumMedia::CHARS_LIMIT],
			albumName[MusicAlbumMedia::CHARS_LIMIT];

	readLine("Enter the artist's name: ", artistName,
			MusicAlbumMedia::CHARS_LIMIT);
	readLine("Enter the album name: ", albumName, MusicAlbumMedia::CHARS_LIMIT);

	return (MusicAlbumMedia *) m_register.findMedia(artistName, albumName);
}

void MediaApplication::showArtistAlbums() {
	char artistName[MusicAlbumMedia::CHARS_LIMIT];
	readLine("What's the artist's name?: ", artistName,
			MusicAlbumMedia::CHARS_LIMIT);
	std::vector<BaseMedia *> media = m_register.findMedia(artistName);

	if (media.size() < 1) {
		cout << "Cannot find artist " << artistName << '!' << endl;
		return;
	}

	for (std::vector<BaseMedia *>::const_iterator i = media.begin();
			i != media.end(); ++i) {
		cout << **i << endl;
		delete *i;
	}
}

int MediaApplication::run() {
	char choice = '\0';
	choice = 'y';
	MusicAlbumMedia *album = NULL;

#ifdef _DEBUG
	{

		do {
			cout << "Run test first?: ";
			//InputOutput::readChar(choice);
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
		case Main::MenuItems::LOAD_LIBRARY:
			try {
				m_register.loadReg();
				cout << "Successfully loaded the register from file." << endl;
			} catch (const invalid_argument &e) {
				cout << "Couldn't load the register from file." << endl;
			}

			readEnter();
			break;

		case Main::MenuItems::SAVE_LIBRARY:
			try {
				m_register.saveReg();
				cout << "Successfully saved the register to file." << endl;
			} catch (const invalid_argument &e) {
				cout << "Couldn't load the register to file." << endl;
			}

			readEnter();
			break;

		case Main::MenuItems::SHOW_LIBRARY:
			m_register.showMedia();
			readEnter();
			break;

		case Main::MenuItems::SORT_LIBRARY:
			m_register.sortMedia();
			cout << "Library was sorted!" << endl;
			readEnter();
			break;

		case Main::MenuItems::ADD_ALBUM:
			m_register.addMedia(createAlbum());
			cout << "Album was added!" << endl;
			readEnter();
			break;

		case Main::MenuItems::MANAGE_ALBUM:
			album = findAlbum();

			if (album == NULL) {
				cout << "Couldn't find album with those credentials!" << endl;
				readEnter();
				break;
			}

			manageAlbum(*album);
			delete album;
			break;

		case Main::MenuItems::SHOW_ARTIST_ALBUMS:
			showArtistAlbums();
			readEnter();
			break;

		default:
			if (choice != Main::MenuItems::QUIT) {
				throw invalid_argument("Invalid menu option selected!");
			}
		}
	} while (choice != Main::MenuItems::QUIT);

	return EXIT_SUCCESS;
}

void MediaApplication::manageAlbum(MusicAlbumMedia a_album) {
	int choice = 0;
	MusicAlbumMedia tmpAlbum;

	do {
		choice = m_menu.select(1);

		switch (choice) {
		case Album::MenuItems::SHOW:
			cout << "Currently selected album is: " << a_album << endl;
			readEnter();
			break;

		case Album::MenuItems::EDIT:
			tmpAlbum = createAlbum();
			m_register.replaceMedia(a_album, tmpAlbum);
			a_album = tmpAlbum;
			break;

		case Album::MenuItems::REMOVE:
			removeAlbum(a_album);
			readEnter();
			choice = Album::MenuItems::QUIT;
			break;

		default:
			if (choice != Album::MenuItems::QUIT) {
				throw runtime_error("Invalid menu option selected!");
			}
			break;
		}
	} while (choice != Album::MenuItems::QUIT);
}

int main() {
	MediaApplication app;
	return app.run();
}
