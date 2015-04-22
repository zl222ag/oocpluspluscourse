#ifndef FRACTION_CPP
#define FRACTION_CPP

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "fraction.h"

using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::runtime_error;
using std::abs;
using std::numeric_limits;
using std::streamsize;

#pragma region Friends

#pragma region Stream
// Reads user input, called by cin.
// May throw exception zero_divisor_error if denominator is equal to zero.
istream &operator>>(istream &a_istream, Fraction &a_f)
throw (zero_division_error) {
	int temp1 = 1, temp2 = 1;

	a_istream.clear();

	Fraction::getInteger(a_istream, "Enter numerator: ", temp1);
	Fraction::getInteger(a_istream, "Enter denominator: ", temp2);

	a_f.set(temp1, temp2);

	cout << "Result for input: " << a_f << endl;

	return a_istream;
}
#pragma endregion Stream

#pragma endregion Friends

// Calculates and returns the greatest common divisor of two values.
int Fraction::gcd(const int a_num, const int a_den) {
	int m = abs(a_num), n = abs(a_den);

	while (m > 0) {
		if (n > m) {
			swap(n, m);
		}
		m -= n;
	}

	return n;
}

// Sets the values for fraction numerator and, denominator.
// May throw exception zero_divisor_error if denominator is equal to zero.
void Fraction::set(int a_numerator, int a_denominator)
throw (zero_division_error) {
	if (a_denominator == 0) {
		throw zero_division_error("The the denominator "
			"cannot have value zero!");
	}

	if (a_numerator > 0 && a_denominator < 0) {
		a_numerator = -a_numerator;
		a_denominator = -a_denominator;
	} else if (a_numerator < 0 && a_denominator < 0) {
		a_numerator = abs(a_numerator);
		a_denominator = abs(a_denominator);
	}

	int temp = Fraction::gcd(a_numerator, a_denominator);
	m_numerator = a_numerator / temp;
	m_denominator = a_denominator / temp;
}

// Asks user for input, to be used only for istream operator>>.
// Ignores input until actual integers are written.
void Fraction::getInteger(istream &a_istream, const char *a_text,
	int &a_temp1) {
	bool error = false;

	do {
		cout << a_text;
		a_istream >> a_temp1;
		error = a_istream.fail();
		cout << endl;
		a_istream.clear();
		a_istream.ignore(numeric_limits<streamsize>::max(), '\n');

		if (error) {
			cout << "Invalid value, try again!" << endl;
		}
	} while (error);
}
#endif // FRACTION_CPP
