#include <inputoutput.h>

using std::cout;
using std::clog;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;

// Reads a number from the user (repeated until it's not an error).
void InputOutput::readInteger(const char *a_text, int &a_value, int a_min,
	const char *a_lowErr /*NULL*/, const char *a_miscError /*NULL*/) {
	int temp;
	bool error = false;

	do {
		cout << a_text;
		cin >> temp;
		error = !cin.good();
		cin.clear();
		readEnter();
		cout << endl;

		if (a_lowErr != NULL && temp > a_min) {
			clog << a_lowErr << endl;
		} else if (a_miscError != NULL && error) {
			clog << a_miscError << endl;
		}
	} while (error || temp < a_min);

	a_value = temp;
}

// Reads a number from the user (repeated until it's not an error).
// May throw runtime_error if a_min is greater than a_max
void InputOutput::readInteger(const char *a_text, int &a_value, int a_min,
	int a_max, const char *a_lowErr /*NULL*/, const char *a_highErr /*NULL*/,
	const char *a_miscError /*NULL*/) throw(std::runtime_error) {
	int temp;
	bool error = false;

	if (a_min > a_max) {
		throw std::runtime_error(
				"Error: a_min cannot possibly be greater than a_max!");
	}

	do {
		cout << a_text;
		cin >> temp;
		error = !cin.good();
		cin.clear();
		readEnter();
		cout << endl;

		if (a_lowErr != NULL && temp < a_min) {
			clog << a_lowErr << endl;
		} else if (a_highErr != NULL && temp > a_max) {
			clog << a_highErr << endl;
		} else if (a_miscError != NULL && error) {
			clog << a_miscError << endl;
		}
	} while (error || temp < a_min || temp > a_max);

	a_value = temp;
}
