#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>
#include <istream>

class Fraction {
	friend std::ostream &operator<<(std::ostream &, const Fraction &);
	friend std::istream &operator>>(std::istream &, const Fraction &);

	friend Fraction operator+(const Fraction &, int);
	friend Fraction operator+(int, const Fraction &);

	friend Fraction operator-(const Fraction &, int);
	friend Fraction operator-(int, const Fraction &);

	friend Fraction operator*(const Fraction &, int);
	friend Fraction operator*(int, const Fraction &);

	friend Fraction operator/(const Fraction &, int);
	friend Fraction operator/(int, const Fraction &);

	int m_numerator = 0, m_denominator = 0;

public:
	Fraction(int a_numerator = 1, int a_denominator = 1) {
		m_numerator = a_numerator;
		m_denominator = a_denominator;
	}

	~Fraction() {

	}

	Fraction operator+(const Fraction &) const;
	Fraction operator-(const Fraction &) const;
	Fraction operator*(const Fraction &) const;
	Fraction operator/(const Fraction &) const;
};

#endif // FRACTION_H
