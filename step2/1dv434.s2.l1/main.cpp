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
	static const char *ALPHABET;

	Clock *m_clock = NULL;

public:
	App() {
		m_clock = new Clock();
	}

	~App() {
		delete m_clock;
	}

	int run();

	// Ignores input until a new line, or enter
	static void readEnter() {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void resetStartCounter(MyTime &a_time) {
		readEnter();
		a_time = m_clock->give_me_the_time();
	}
};
const char *App::ALPHABET = "abcdefghijklmnopqrstuvwxyz";

int App::run() {
	MyTime startTime, endTime;
	bool error = false, rightValue = false;
	char userInput[strlen(ALPHABET)];

	cout << "Write the english alphabet as fast as you can!" << endl <<
		"Press enter and then write the alphabet and proceed with enter!";

	resetStartCounter(startTime);

	do {
		cin >> userInput;
		error = cin.fail();
		cin.clear();
		if (!error) {
			rightValue = Compare::equal(userInput, ALPHABET);
			if (!rightValue) {
				cout << "Sorry, the english alphabet please." << endl;
				resetStartCounter(startTime);
			}
		} else {
			cerr << "Erroneous input, sorry!" << endl;
			resetStartCounter(startTime);
		}
	} while (!rightValue);

	endTime = m_clock->give_me_the_time();

	cout << "Total time: " << endTime - startTime << endl;

	return EXIT_SUCCESS;
}

int main() {
	App app;

	return app.run();
}
