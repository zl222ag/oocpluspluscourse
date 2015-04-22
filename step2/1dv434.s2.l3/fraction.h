#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>
#include <istream>
#include <stdexcept>

class zero_division_error : public std::logic_error {
public:
	zero_division_error(const char *a_msg) : std::logic_error(a_msg) {
	}
};

class Fraction {
	friend std::ostream &operator<<(std::ostream &a_ostream,
		const Fraction &a_f) {
		a_ostream << a_f.m_numerator << "/" << a_f.m_denominator;

		return a_ostream;
	}

	friend std::istream &operator>>(std::istream &, Fraction &)
		throw (zero_division_error);

	friend Fraction operator+(int a_int, const Fraction &a_f) {
		return Fraction(
			a_int * a_f.m_denominator +
			a_f.m_numerator * 1,
			1 * a_f.m_denominator);
	}

	friend Fraction operator-(int a_int, const Fraction &a_f) {
		return Fraction(
			a_int * a_f.m_denominator -
			a_f.m_numerator * 1,
			1 * a_f.m_denominator);
	}

	friend Fraction operator*(int a_int, const Fraction &a_f) {
		return Fraction(
			a_int * a_f.m_numerator,
			1 * a_f.m_denominator);
	}

	friend Fraction operator/(int a_int, const Fraction &a_f) {
		return Fraction(
			a_int * a_f.m_denominator,
			1 * a_f.m_numerator);
	}

	friend bool operator==(int a_int, const Fraction &a_f) {
		return a_int == a_f.m_numerator && 1 == a_f.m_denominator;
	}

	friend bool operator!=(int a_int, const Fraction &a_f) {
		return a_int != a_f.m_numerator || 1 != a_f.m_denominator;
	}


	int m_numerator = 0, m_denominator = 0;

	// Swaps values of two int variables.
	static void swap(int &a_a, int &a_b) {
		int tmp = a_a;
		a_a = a_b;
		a_b = tmp;
	}

	// Calculates and returns the greatest common divisor of two values.
	static int gcd(const int a_num, const int a_den);

	// Sets the values for fraction numerator and, denominator.
	// May throw exception zero_divisor_error if denominator is equal to zero.
	void set(int a_numerator, int a_denominator)
		throw (zero_division_error);

	static void getInteger(std::istream &, const char *, int &);

public:
	// May throw exception zero_divisor_error if denominator is equal to zero.
	Fraction(int a_numerator = 1, int a_denominator = 1)
		throw (zero_division_error) {
		set(a_numerator, a_denominator);
	}

	Fraction operator+(int a_int) const {
		return Fraction(
			m_numerator * 1 +
			a_int * m_denominator,
			m_denominator * 1);
	}

	Fraction operator-(int a_int) const {
		return Fraction(
			m_numerator * 1 -
			a_int * m_denominator,
			m_denominator * 1);
	}

	Fraction operator*(int a_int) const {
		return Fraction(
			m_numerator * a_int,
			m_denominator * 1);
	}

	Fraction operator/(int a_int) const{
		return Fraction(
			m_numerator * 1,
			m_denominator * a_int);
	}

	bool operator==(int a_int) const {
		return m_numerator == a_int && m_denominator == 1;
	}

	bool operator!=(int a_int) const {
		return m_numerator != a_int || m_denominator != 1;
	}

	Fraction operator+(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator +
			a_b.m_numerator * m_denominator,
			m_denominator * a_b.m_denominator);
	}

	Fraction operator-(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator -
			a_b.m_numerator * m_denominator,
			m_denominator * a_b.m_denominator);
	}

	Fraction operator*(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_numerator,
			m_denominator * a_b.m_denominator);
	}

	Fraction operator/(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator,
			m_denominator * a_b.m_numerator);
	}

	Fraction operator=(const Fraction &a_b) {
		m_numerator = a_b.m_numerator;
		m_denominator = a_b.m_denominator;

		return *this;
	}

	bool operator==(const Fraction &a_b) const {
		return m_numerator == a_b.m_numerator && m_denominator == a_b.m_denominator;
	}

	bool operator!=(const Fraction &a_b) const {
		return m_numerator != a_b.m_numerator || m_denominator != a_b.m_denominator;
	}
};

#endif // FRACTION_H
