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
void readEnter();
void readChar(char &);
void showFileError(exception &);
bool getMaxMin(ifstream &, double &, double &);
bool getMean(ifstream &, double &);
bool outputValues(ifstream &);
#pragma endregion

/*
 * Här körs programmet.
 * Den ska kunna via menyn visa temperatur,
 * maximum och minimum, medelvärdet och man kan kunna stänga den.
 */
int main() {
	bool looping = true;
	double total = 0, mean = 0, max = 0, min = 0;
	char userChoice;
	ifstream inputFile;
	inputFile.exceptions(ios::failbit);

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
		system("cls"); // clears screen.
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

		try {
			inputFile.open(LOG_FILE);
		} catch (exception &e) {
			showFileError(e);
			cerr << endl << "Press enter to terminate the program" << endl;
			readEnter();

			return EXIT_FAILURE;
		}

		//		if (fil.tellg() > 0) {
		//			fil.clear();
		//			fil.seekg(0, ios::beg);
		//		}

		switch (userChoice) {
		case '1':
			cout << endl << "Displaying the latest " << NUMBER_OF_VALUES << " temperature values:" << endl << endl;

			if (!outputValues(inputFile)) {
				break;
			}

			break;

		case '2':
			cout << endl << "Calculating the maximum and minimum temperature..." << endl;

			if (!getMaxMin(inputFile, max, min)) {
				break;
			}

			cout << endl << "Maximum temperature: " << fixed << setprecision(PRECISION) << max << " degrees Celcius" << endl;
			cout << endl << "Minimum temperature: " << min << " degrees Celcius" << endl;
			break;

		case '3':
			cout << endl << "Calculating average temperature..." << endl;

			if (!getMean(inputFile, mean)) {
				break;
			}

			cout << endl << "Average temperature: ";
			cout << " " << fixed << setprecision(PRECISION) << mean << " degrees Celcius" << endl;
			break;

		case '4':
			looping = false;
			cout << endl << endl << "Terminating the program.";
			break;

		default:
			cout << endl << endl << "Invalid menu option.";
			break;
		}
		cout << endl << endl << "Press Enter to continue:";
		readEnter();
		inputFile.close();
	}
	return EXIT_SUCCESS;
}

void readEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void readChar(char &a_userChoice) {
	cin.get(a_userChoice);
	readEnter();
}

void showFileError(exception &a_e) {
	cerr << "An Error occured while reading file: " << endl << "\t" << a_e.what() << endl;
}

bool outputValues(ifstream  &a_fil) {
	double temp = 0.0;

	try {
		for (int i = 0; i < NUMBER_OF_VALUES; ++i) {
			if (i % 6 == 0) {
				cout << endl;
			}
			a_fil >> temp;
			cout << fixed << setprecision(PRECISION) << setw(NUMBER_WIDTH) << temp;
		}
	} catch (exception &e) {
		showFileError(e);
		return false;
	}
	return true;
}

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
	} catch (exception &e) {
		showFileError(e);
		return false;
	}
	return true;
}

bool getMean(ifstream &a_fil, double &a_mean) {
	double temp = 0.0;
	double total = 0.0;

	try {
		for (int i = 0; i < NUMBER_OF_VALUES; ++i) {
			a_fil >> temp;
			total += temp;
		}
	} catch (exception &e) {
		showFileError(e);
		return false;
	}

	a_mean = total / (double) NUMBER_OF_VALUES;

	return true;
}
