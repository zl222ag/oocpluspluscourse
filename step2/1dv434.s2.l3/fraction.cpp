#ifndef FRACTION_CPP
#define FRACTION_CPP

#include <cmath>
#include <iostream>
#include <stdexcept>
#include "fraction.h"

using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::runtime_error;

#pragma region Friends

#pragma region Stream
ostream &operator<<(ostream &a_ostream, const Fraction &a_f) {
	a_ostream << a_f.m_numerator << " / " << a_f.m_denominator;

	return a_ostream;
}

istream &operator>>(istream &a_istream, Fraction &a_f) {
	int temp = 1;
	cout << "Enter numerator: ";
	a_istream >> temp;
	a_f.m_numerator = temp;
	cout << endl;
	a_istream.clear();

	cout << "Enter denominator: ";
	temp = 1;
	a_istream >> temp;
	a_f.m_denominator = temp;
	cout << endl;
	a_istream.clear();

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
		1 * a_f.m_denominator -
		a_f.m_numerator * a_int,
		a_int * a_f.m_denominator);
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

#endif // FRACTION_CPP
