#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>
#include <istream>
#include <stdexcept>

class zero_division_error : public std::exception {
public:
	zero_division_error(const char *a_msg) : std::exception(a_msg) {
	}
};

class Fraction {
	friend std::ostream &operator<<(std::ostream &, const Fraction &);
	friend std::istream &operator>>(std::istream &, Fraction &);

	friend Fraction operator+(const Fraction &, int);
	friend Fraction operator+(int, const Fraction &);

	friend Fraction operator-(const Fraction &, int);
	friend Fraction operator-(int, const Fraction &);

	friend Fraction operator*(const Fraction &, int);
	friend Fraction operator*(int, const Fraction &);

	friend Fraction operator/(const Fraction &, int);
	friend Fraction operator/(int, const Fraction &);

	int m_numerator = 0, m_denominator = 0;

	static void swap(int &a_a, int &a_b) {
		int tmp = a_a;
		a_a = a_b;
		a_b = tmp;
	}

	static int gcd(const int a_num, const int a_den);

	void set(int a_numerator = 1, int a_denominator = 1)
		throw (zero_division_error);

public:
	Fraction(int a_numerator = 1, int a_denominator = 1)
		throw (zero_division_error) {
		set(a_numerator, a_denominator);
	}

	Fraction Fraction::operator+(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator +
			a_b.m_numerator * m_denominator,
			m_denominator * a_b.m_denominator);
	}

	Fraction Fraction::operator-(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator -
			a_b.m_numerator * m_denominator,
			m_denominator * a_b.m_denominator);
	}

	Fraction Fraction::operator*(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_numerator,
			m_denominator * a_b.m_denominator);
	}

	Fraction Fraction::operator/(const Fraction &a_b) const {
		return Fraction(
			m_numerator * a_b.m_denominator,
			m_denominator * a_b.m_numerator);
	}

	Fraction Fraction::operator=(const Fraction &a_b) {
		if (a_b.m_numerator == 0) {
			m_numerator = 0;
		}
		if (a_b.m_denominator == 0) {
			m_denominator = 0;
			return *this;
		}

		int temp = Fraction::gcd(a_b.m_numerator, a_b.m_denominator);
		m_numerator = a_b.m_numerator / temp;
		m_denominator = a_b.m_denominator / temp;

		return *this;
	}

	bool Fraction::operator==(const Fraction &a_b) const {
		return m_numerator == a_b.m_numerator && m_denominator == a_b.m_denominator;
	}

	bool Fraction::operator!=(const Fraction &a_b) const {
		return m_numerator != a_b.m_numerator || m_denominator != a_b.m_denominator;
	}
};

#endif // FRACTION_H
