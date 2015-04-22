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

const char *Fraction::NUMERATOR_ZERO_ERROR_MSG = "The numerator cannot have "
"value zero!";

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
			cout << "invalid value, try again!" << endl;
		}
	} while (error);
}

#pragma region Friends

#pragma region Stream
ostream &operator<<(ostream &a_ostream, const Fraction &a_f) {
	a_ostream << a_f.m_numerator << "/" << a_f.m_denominator;

	return a_ostream;
}

istream &operator>>(istream &a_istream, Fraction &a_f) {
	int temp1 = 1, temp2 = 1;

	a_istream.clear();

	Fraction::getInteger(a_istream, "Enter numerator: ", temp1);
	Fraction::getInteger(a_istream, "Enter denominator: ", temp2);

	a_f.set(temp1, temp2);

	cout << "Result for input: " << a_f.m_numerator << " / " <<
		a_f.m_denominator << endl;

	return a_istream;
}
#pragma endregion Stream

#pragma region Addition
Fraction operator+(const Fraction &a_f, int a_int) {
	return Fraction(
		a_f.m_numerator * 1 +
		a_int * a_f.m_denominator,
		a_f.m_denominator * 1);
}

Fraction operator+(int a_int, const Fraction &a_f) {
	return Fraction(
		a_int * a_f.m_denominator +
		a_f.m_numerator * 1,
		1 * a_f.m_denominator);
}
#pragma endregion Addition

#pragma region Subtraction
Fraction operator-(const Fraction &a_f, int a_int) {
	return Fraction(
		a_f.m_numerator * 1 -
		a_int * a_f.m_denominator,
		a_f.m_denominator * 1);
}

Fraction operator-(int a_int, const Fraction &a_f) {
	return Fraction(
		a_int * a_f.m_denominator -
		a_f.m_numerator * 1,
		1 * a_f.m_denominator);
}
#pragma endregion Subtraction

#pragma region Multiplication
Fraction operator*(const Fraction &a_f, int a_int) {
	return Fraction(
		a_f.m_numerator * a_int,
		a_f.m_denominator * 1);
}

Fraction operator*(int a_int, const Fraction &a_f) {
	return Fraction(
		a_int * a_f.m_numerator,
		1 * a_f.m_denominator);
}
#pragma endregion Multiplication

#pragma region Division
Fraction operator/(const Fraction &a_f, int a_int) {
	return Fraction(
		a_f.m_numerator * 1,
		a_f.m_denominator * a_int);
}

Fraction operator/(int a_int, const Fraction &a_f) {
	return Fraction(
		a_int * a_f.m_denominator,
		1 * a_f.m_numerator);
}
#pragma endregion Division

#pragma region Comparison
bool operator==(const Fraction &a_f, int a_int) {
	if (a_int == 0) {
		throw zero_division_error(Fraction::NUMERATOR_ZERO_ERROR_MSG);
	}

	return a_f.m_numerator == a_int && a_f.m_denominator == 1;
}

bool operator==(int a_int, const Fraction &a_f) {
	if (a_int == 0) {
		throw zero_division_error(Fraction::NUMERATOR_ZERO_ERROR_MSG);
	}

	return a_int == a_f.m_numerator && 1 == a_f.m_denominator;
}

bool operator!=(const Fraction &a_f, int a_int) {
	if (a_int == 0) {
		throw zero_division_error(Fraction::NUMERATOR_ZERO_ERROR_MSG);
	}

	return a_f.m_numerator != a_int || a_f.m_denominator != 1;
}

bool operator!=(int a_int, const Fraction &a_f) {
	if (a_int == 0) {
		throw zero_division_error(Fraction::NUMERATOR_ZERO_ERROR_MSG);
	}

	return a_int != a_f.m_numerator || 1 != a_f.m_denominator;
}
#pragma endregion Comparison

#pragma endregion Friends

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

void Fraction::set(int a_numerator /*= 1*/, int a_denominator/* = 1*/)
throw (zero_division_error) {
	if (a_numerator == 0 || a_denominator == 0) {
		throw zero_division_error("The numerator nor the denominator "
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

#endif // FRACTION_CPP
