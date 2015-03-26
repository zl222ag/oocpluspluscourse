// miserable.cpp
// Datum: 2015-03-23
// Programmerare: Zlatko Ladan
// Kort beskrivning: Fixa så koden följer kodstandarden.

#define LOG_FILE "templog.txt"
#define NUMBER_OF_VALUES 24

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
#pragma endregion

#pragma region header
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
	int i;
	double total = 0, mean = 0, max = 0, min = 0;
	char userChoice;
	ifstream fil;
	fil.exceptions(ios::failbit);

	cout << endl << endl <<
		"Temperature Statistics" << endl <<
		"----------------------" << endl <<
		endl <<
		"Reading logged values for processing and presentation..." << endl <<
		endl <<
		"Press Enter for menu: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.clear();

	while (looping) {
		system("cls");
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
		cin.get(userChoice);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		fil.open(LOG_FILE);

		if (fil.tellg() > 0) {
			fil.clear();
			fil.seekg(0, ios::beg);
		}

		switch (userChoice) {
		case '1':
			cout << endl << "Displaying the latest " << NUMBER_OF_VALUES << " temperature values:" << endl << endl;

			outputValues(fil);

			break;

		case '2':
			cout << endl << "Calculating the maximum and minimum temperature..." << endl;

			getMaxMin(fil, max, min);

			cout << endl << "Maximum temperature: " << fixed << setprecision(2) << max << " degrees Celcius" << endl;
			cout << endl << "Minimum temperature: " << min << " degrees Celcius" << endl;
			break;

		case '3':
			cout << endl << "Calculating average temperature..." << endl;

			getMean(fil, mean);

			cout << endl << "Average temperature: ";
			cout << " " << fixed << setprecision(2) << mean << " degrees Celcius" << endl;
			break;

		case '4':
			looping = false;
			cout << endl << endl << "Terminating the program.";
			break;

		default:
			cout << endl << endl << "Illegal menu option.";
			break;
		}
		cout << endl << endl << "Press Enter to continue:";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		fil.close();
	}
	return EXIT_SUCCESS;
}

bool outputValues(ifstream  &fil) {
	double temp;

	try {
		for (int i = 0; i < NUMBER_OF_VALUES; i++) {
			if (i % 6 == 0) {
				cout << endl;
			}
			fil >> temp;
			cout << fixed << setprecision(2) << setw(8) << temp;
		}
	} catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}
	return true;
}

bool getMaxMin(ifstream &fil, double &max, double &min) {
	double temp;
	fil >> temp;
	max = min = temp;

	try {
		for (int i = 1; i < NUMBER_OF_VALUES; i++) {
			fil >> temp;
			if (temp > max) {
				max = temp;
			}
			if (temp < min) {
				min = temp;
			}
		}
	} catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}
	return true;
}

bool getMean(ifstream &fil, double &mean) {
	double temp;
	double total = 0.0;
	try {
		for (int i = 0; i < NUMBER_OF_VALUES; i++) {
			fil >> temp;
			total += temp;
		}
	} catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}
	mean = total / (double) NUMBER_OF_VALUES;
	return true;
}
