// 1dv434.s2.l1/main.cpp
// Datum: 2015-04-15
// Programmerare: Zlatko Ladan
// Kort beskrivning: skriv alphabetet så snabbt som möjligt.

#include <cstdlib>
#include <iostream>
#include <limits>
#include <cstring>
#include <Clock.h>
#include <MyTime.h>
#include <compare.h>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

class App {
	static const char *ALPHABET; // "abcdefghijklmnopqrstuvwxyz"
	static const int ALPHABET_LENGTH_STR = 27; // strlen(ALPHABET) + 1
	Clock *m_clock = NULL;

public:
	App() {
		m_clock = new Clock();
	}

	~App() {
		delete m_clock;
	}

	int run();

	// Ignores input until a new line, or enter.
	static void readEnter() {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Waits for user to press enter
	// after that resets a_time
	void resetStartCounter(MyTime &a_time) {
		readEnter();
		a_time = m_clock->give_me_the_time();
	}
};
const char *App::ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int App::run() {
	MyTime startTime, endTime;
	bool error = false, rightValue = false;
	char userInput[ALPHABET_LENGTH_STR], doContinue = '\0';

	cout << "Write the english alphabet as fast as you can!" << endl <<
		"Press enter and then write the alphabet and proceed with enter!";

	do {
		resetStartCounter(startTime);

		do {
			cin.getline(userInput, ALPHABET_LENGTH_STR);
			error = cin.fail();
			cin.clear();

			if (!error) {
				rightValue = Compare::equal(userInput, ALPHABET);

				if (!rightValue) {
					cout << "Sorry, the english alphabet please." << endl <<
						"Press enter to restart";
					resetStartCounter(startTime);
				}
			} else {
				cerr << "Erroneous input, sorry!" << endl <<
					"Press enter to restart";
				resetStartCounter(startTime);
			}
		} while (!rightValue);

		endTime = m_clock->give_me_the_time();
		cout << "Total time: " << endTime - startTime << ", good, i guess!" <<
			endl;

		do {
			cout << "Try beating it [y|n]?:";
			cin.get(doContinue);

			if (!cin.fail()) {
				doContinue = tolower(doContinue);
			}
			cin.clear();
			cout << endl;
		} while (doContinue != 'y' && doContinue != 'n');
	} while (doContinue == 'y');

	return EXIT_SUCCESS;
}

// Starts from the beginning.
int main() {
	App app;

	return app.run();
}
