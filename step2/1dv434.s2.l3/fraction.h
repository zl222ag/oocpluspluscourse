#ifndef FRACTION_H
#define FRACTION_H

class Fraction {
public:
	Fraction();
	~Fraction();

	Fraction operator+(Fraction);
	Fraction operator-(Fraction);
	Fraction operator*(Fraction);
	Fraction operator/(Fraction);
};

#endif // FRACTION_H
