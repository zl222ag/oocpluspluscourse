// miserable.cpp
// Datum: 2015-03-23
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa så koden följer kodstandarden.

#define LOG_FILE "templog.txt"
#define NUMBER_OF_VALUES 24
#define PRECISION 2
#define NUMBER_WIDTH 8

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdlib>

#pragma region Using
using std::cout;
using std::cin;
using std::cerr;
using std::ios;
using std::endl;
using std::ifstream;
using std::exception;
using std::fixed;
using std::setprecision;
using std::setw;
using std::numeric_limits;
using std::streamsize;
#pragma endregion

#pragma region header
void clearScreen();
void readEnter();
void readChar(char &);
void showFileError(ifstream::failure &);
bool getMaxMin(ifstream &, double &, double &);
bool getMean(ifstream &, double &);
bool outputValues(ifstream &);
#pragma endregion

/* The starter function for the program.
 * It should be able to show a menu with choices:
 * show all temperatures,
 * show max and min,
 * show mean temperature, and
 * It should also be closeable.
 */
int main() {
	bool looping = true;
	double mean = 0.0, max = 0.0, min = 0.0;
	char userChoice;
	ifstream inputFile;
	// Causes exception to be thrown when an error occures on I/O operation or a
	// read/write occures on I/O operations.
	// source: http://www.cplusplus.com/reference/ios/ios/exceptions/
	inputFile.exceptions(ios::failbit | ios::badbit);

	cout << endl << endl <<
		"Temperature Statistics" << endl <<
		"----------------------" << endl <<
		endl <<
		"Reading logged values for processing and presentation..." << endl <<
		endl <<
		"Press Enter for menu: ";
	readEnter();
	cin.clear();

	while (looping) {
		clearScreen();
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
		readChar(userChoice);
		clearScreen();

		try {
			inputFile.open(LOG_FILE);
		} catch (ifstream::failure &e) {
			showFileError(e);
			cerr << endl << "Press enter to terminate the program..." << endl;
			readEnter();

			return EXIT_FAILURE;
		}

		cout << endl << endl; // results should be lower in console.
		switch (userChoice) {
		case '1':
			cout << "Displaying the latest " << NUMBER_OF_VALUES <<
				" temperature values:" << endl << endl;

			if (!outputValues(inputFile)) {
				break;
			}

			break;

		case '2':
			cout << "Calculating the maximum and minimum temperature..." <<
				endl;

			if (!getMaxMin(inputFile, max, min)) {
				break;
			}

			cout << endl << "Maximum temperature: " << fixed <<
				setprecision(PRECISION) << max << " degrees Celcius" << endl;

			cout << endl << "Minimum temperature: " << min << " degrees Celcius"
				<< endl;
			break;

		case '3':
			cout << "Calculating average temperature..." << endl;

			if (!getMean(inputFile, mean)) {
				break;
			}

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
		readEnter();
		inputFile.close();
	}
	return EXIT_SUCCESS;
}

// Clears the console screen.
void clearScreen() {
	system("cls");
}

// Ignores all user's input until the enter key is pressed.
// source: http://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
void readEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads the user's input (ignores all characters except the first).
void readChar(char &a_userChoice) {
	cin.get(a_userChoice);
	readEnter();
}

// Shows an error.
void showFileError(ifstream::failure &a_e) {
	cerr << endl << "An Error occured while reading file: " << endl << "\t" <<
		a_e.what() << endl;
}

// Reads values from file and shows them in a formatted table.
bool outputValues(ifstream  &a_fil) {
	double temp = 0.0;

	try {
		for (int i = 0; i < NUMBER_OF_VALUES; ++i) {
			if (i % 6 == 0) {
				cout << endl;
			}
			a_fil >> temp;
			cout << fixed << setprecision(PRECISION) << setw(NUMBER_WIDTH) <<
				temp;
		}
	} catch (ifstream::failure &e) {
		showFileError(e);
		return false;
	}
	return true;
}

// Reads values from file and gets the max and min values.
bool getMaxMin(ifstream &a_fil, double &a_max, double &a_min) {
	double temp = 0.0;

	try {
		a_fil >> temp;
		a_max = a_min = temp;

		for (int i = 1; i < NUMBER_OF_VALUES; ++i) {
			a_fil >> temp;
			if (temp > a_max) {
				a_max = temp;
			}
			if (temp < a_min) {
				a_min = temp;
			}
		}
	} catch (ifstream::failure &e) {
		showFileError(e);
		return false;
	}
	return true;
}

// Reads values from file and gets the mean values.
bool getMean(ifstream &a_fil, double &a_mean) {
	double temp = 0.0;
	double total = 0.0;

	try {
		for (int i = 0; i < NUMBER_OF_VALUES; ++i) {
			a_fil >> temp;
			total += temp;
		}
	} catch (ifstream::failure &e) {
		showFileError(e);
		return false;
	}

	a_mean = total / (double) NUMBER_OF_VALUES;

	return true;
}
