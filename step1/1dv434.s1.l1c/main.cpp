// miserable.cpp
// Datum: 2015-04-04
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa så koden använder sig utav klasser

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "inputoutput.h"
#include "temperature.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::runtime_error;

class App {
private:
	static const int PRECISION = 2;
	static const int NUMBER_WIDTH = 8;
	static const int VALUES_PER_ROW = 6;
	static char *LOG_FILE /*= "templog.txt"*/;

	// Reads values from file and shows them in a formatted table.
	void outputValues(Temperature *);

public:
	int run();
};

char *App::LOG_FILE = "templog.txt";

// Reads values from file and shows them in a formatted table.
void App::outputValues(Temperature *a_temp) {
	for (int i = 0; i < a_temp->getSize(); ++i) {
		if (i % VALUES_PER_ROW == 0) {
			cout << endl;
		}

		cout << fixed << setprecision(PRECISION) << setw(NUMBER_WIDTH) <<
			a_temp->get(i);
	}
	cout << endl;
}

// Runs the application's logic
int App::run() {
	bool looping = true;
	double mean = 0.0, max = 0.0, min = 0.0;
	char userChoice;
	Temperature *temperature = new Temperature();
	InputOutput::clearScreen();

	cout << endl << endl <<
		"Temperature Statistics" << endl <<
		"----------------------" << endl <<
		endl <<
		"Reading logged values for processing and presentation..." << endl <<
		endl <<
		"Press Enter for menu: ";
	InputOutput::readEnter();

	try {
		temperature->LoadTemperatures(LOG_FILE);
	} catch (runtime_error &e) {
		InputOutput::clearScreen();

		cerr << endl << "An Error occured while reading file: " << endl
			<< "\t" << e.what() <<
			endl << endl <<
			"Press enter to terminate the program...";
		InputOutput::readEnter();

		return EXIT_FAILURE;
	}

	while (looping) {
		InputOutput::clearScreen();
		cout << endl <<
			endl <<
			"MENU" << endl <<
			"----" << endl <<
			endl <<
			"1. Display temperature values" << endl <<
			"2. View maximum and minimum temperatures" << endl <<
			"3. View average temperature" << endl <<
			"4. Quit" << endl <<
			endl <<
			"Make your choice: ";
		InputOutput::readChar(userChoice);
		InputOutput::clearScreen();

		cout << endl << endl; // results should be lower in console.
		switch (userChoice) {
		case '1':
			cout << "Displaying the latest " << temperature->getSize() <<
				" temperature values:" << endl << endl;

			outputValues(temperature);

			break;

		case '2':
			cout << "Calculating the maximum and minimum temperature..." <<
				endl;

			temperature->getMaxMin(max, min);

			cout << endl << "Maximum temperature: " << fixed <<
				setprecision(PRECISION) << max << " degrees Celcius" << endl;

			cout << endl << "Minimum temperature: " << min << " degrees Celcius"
				<< endl;
			break;

		case '3':
			cout << "Calculating average temperature..." << endl;

			mean = temperature->getMean();

			cout << endl << "Average temperature: " << fixed <<
				setprecision(PRECISION) << mean << " degrees Celcius" << endl;
			break;

		case '4':
			cout << "Terminating the program." << endl;
			looping = false;
			break;

		default:
			cout << "Invalid menu option." << endl;
			break;
		}
		cout << endl << "Press Enter to continue:";
		InputOutput::readEnter();
	}
	delete temperature;

	return EXIT_SUCCESS;
}

/* The starter function for the program.
 * It should be able to show a menu with choices:
 * show all temperatures,
 * show max and min,
 * show mean temperature, and
 * It should also be closeable.
 */
int main() {
	App app;
	return app.run();
}
