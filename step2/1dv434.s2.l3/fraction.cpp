#ifndef FRACTION_CPP
#define FRACTION_CPP

#include <ostream>
#include <istream>
#include <stdexcept>
#include "fraction.h"

using std::ostream;
using std::istream;
using std::runtime_error;

ostream &operator<<(ostream &a_ostream, const Fraction &a_f) {
	a_ostream << a_f.m_numerator << " / " << a_f.m_denominator;

	return a_ostream;
}

istream &operator>>(istream &a_istream, const Fraction &a_f) {
	throw runtime_error("Not implemented");
}

Fraction operator+(const Fraction & a_f, int a_int) {
	throw runtime_error("Not implemented");
}

Fraction operator+(int a_int, const Fraction &a_f) {
	throw runtime_error("Not implemented");
}

Fraction operator-(const Fraction &a_f, int  a_int) {
	throw runtime_error("Not implemented");
}

Fraction operator-(int  a_int, const Fraction &a_f) {
	throw runtime_error("Not implemented");
}

Fraction operator*(const Fraction &a_f, int  a_int) {
	throw runtime_error("Not implemented");
}

Fraction operator*(int a_int, const Fraction &a_f) {
	throw runtime_error("Not implemented");
}

Fraction operator/(const Fraction &a_f, int  a_int) {
	throw runtime_error("Not implemented");
}

Fraction operator/(int a_int, const Fraction &a_f) {
	throw runtime_error("Not implemented");
}

Fraction Fraction::operator+(const Fraction &a_b) const {
	throw runtime_error("Not implemented");
}

Fraction Fraction::operator-(const Fraction &a_b) const {
	throw runtime_error("Not implemented");
}

Fraction Fraction::operator*(const Fraction &a_b) const {
	throw runtime_error("Not implemented");
}

Fraction Fraction::operator/(const Fraction &a_b) const {
	throw runtime_error("Not implemented");
}

#endif // FRACTION_CPP
