// main.cpp
// Datum: 2015-04-12
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa en mediabibliotekshanterare.

#include <cstdlib>
#include <iostream>
#ifdef _DEBUG
#include "tester.h"
#endif
#include <inputoutput.h>
#include <compare.h>
#include "mediaregister.h"

using std::cout;
using std::endl;

class MediaApplication {
	MediaRegister m_register;

public:
	MediaApplication() {
	}

	int run();
};

int MediaApplication::run() {
#ifdef _DEBUG
	{
		char choice = '\0';

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

	return EXIT_SUCCESS;
}

int main() {
	MediaApplication app;
	return app.run();
}
