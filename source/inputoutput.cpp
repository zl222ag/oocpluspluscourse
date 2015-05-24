#include <inputoutput.h>

// Reads a number from the user (repeated until it's not an error).
void InputOutput::readInteger(const char *a_text, int &a_value, int a_min) {
	int temp;
	bool error = false;

	do {
		cout << a_text;
		cin >> temp;
		error = !cin.good();
		cin.clear();
		readEnter();
		cout << endl;
	} while (error || temp < a_min);

	a_value = temp;
}

// Reads a number from the user (repeated until it's not an error).
// May throw runtime_error if a_min is greater than a_max
void InputOutput::readInteger(const char *a_text, int &a_value, int a_min,
		int a_max) throw(std::runtime_error) {
	int temp;
	bool error = false;

	if (a_min > a_max) {
		throw std::runtime_error(
				"Error: a_mic cannot possibly be greater than a_max!");
	}

	do {
		cout << a_text;
		cin >> temp;
		error = !cin.good();
		cin.clear();
		readEnter();
		cout << endl;
	} while (error || temp < a_min || temp > a_max);

	a_value = temp;
}
