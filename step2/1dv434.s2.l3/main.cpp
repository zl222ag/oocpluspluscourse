// 1dv434.s2.l3/main.cpp
// Datum: 2015-04-16
// Programmerare: Zlatko Ladan
// Kort beskrivning: skriv alphabetet så snabbt som möjligt.

#include <iostream>
#include <inputoutput.h>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

class App {
public:
	App() {
	}

	~App() {
	}

	int run();
};

int App::run() {
	return EXIT_SUCCESS;
}

// Starts from the beginning.
int main() {
	App app;

	cout << "CLEARED" << endl;
	InputOutput::clearScreen();

	return app.run();
}
