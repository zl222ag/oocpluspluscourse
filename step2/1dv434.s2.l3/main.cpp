/*************************************************************************/
// File:	Test2_3.cpp
// Summary:	Test file for Lab 3, Step 2
//          The program will test functionality for class Fraction,
//			which is aimed to represent and handle fractional values.
//			If defined according to requirements in given specification,
//			the result of execution is expected to present outputs
//			like examples suggested in test code comments.
//			NO CHANGES of predefined code are allowed, except ...
//			1. code needed to handle exceptions, if solving optional task
//			2. code aiming to provide the program with quality enhancing
//			details (e.g. an improved, user friendly interface). Such
//			changes should be well motivated in commenting to code.
// Version: Version 1.1 - 2013-04-09
// Author:	Anne Norling
// ------------------------------------------
// Log:		2003-08-25	Created the file. Anne
//			2013-04-08	Uppdate  Version 1.1 by Anne.
//						Converted to English and VS 2012
//			2015-03-06	Revised by Anne. Converted to VS 2013
//			2015-04-19  Tested by Zlatko Ladan for Fraction class.
/*************************************************************************/

#include <iostream>
#include <cassert>
#include <inputoutput.h>
#include "fraction.h"

using std::endl;
using std::cin;
using std::cout;

class Application {
public:
	int run();
	void testUser(Fraction &f1, Fraction &f2);
};

int Application::run() {
	Fraction f1(3, 2);	// numerator=3, denominator=2 ("täljare"=3, "nämnare"=2)
	Fraction f2(10);	// numerator=10, denominator=1
	Fraction result;

	// Testing class Fraction with predefined values
	result = (1 + f1) * (f2 - 3);
	cout << "Following should output \"(1 + 3/2) * (10/1 - 3) = 35/2\", got: "
		<< result << endl;
	assert(result == Fraction(35, 2));

	testUser(f1, f2);

	result = Fraction(5, 2) + 2;
	cout << "Following should output \"5/2 + 2 = 9/2\", got: "
		<< result << endl;
	assert(result == Fraction(9, 2));

	result = Fraction(9, 7) - 6;
	cout << "Following should output \"9/7 - 6 = -33/7\", got: "
		<< result << endl;
	assert(result == Fraction(-33, 7));

	result = Fraction(3, 3) / 5;
	cout << "Following should output \"3/2 / 5 = 1/5\", got: "
		<< result << endl;
	assert(result == Fraction(1, 5));

	result = Fraction(7, 2) * 3;
	cout << "Following should output \"7/2 * 3 = 21/2\", got: "
		<< result << endl;
	assert(result == Fraction(21, 2));

	cout << "Press enter to continue...";
	InputOutput::readEnter();
	return 0;
}

// testing user input.
void Application::testUser(Fraction &f1, Fraction &f2) {
	Fraction result;
	cout << "--begin user test--" << endl;
	cout << "Input two fractions as example: 2/-3 5/6 "
		"(separated by whitespace):" << endl;
	cin >> f1 >> f2;
	InputOutput::readEnter();

	result = f1 + f2;
	cout << "Following should output \"2/-3 + 5/6 = 1/6\", got: " << result <<
		endl;
	assert(result == Fraction(1, 6));

	result = f1 - f2;
	cout << "Following should output \"2/-3 - 5/6 = -3/2\", got: " << result <<
		endl;
	assert(result == Fraction(-3, 2));

	result = f1 * f2;
	cout << "Following should output \"2/-3 * 5/6 = -5/9\", got: " << result <<
		endl;
	assert(result == Fraction(-5, 9));

	result = f1 / f2;
	cout << "Following should output \"2/-3 / 5/6 = -4/5\", got: " << result <<
		endl;
	assert(result == Fraction(-4, 5));
	cout << "--end user test--" << endl << endl;
}

int main() {
	Application myApp;
	return myApp.run();
}
