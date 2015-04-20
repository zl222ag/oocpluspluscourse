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
	void readEnter() {
		cout << "Press enter to continue...";
		InputOutput::readEnter();
	}

	void testUser();
	void test1();
	void test2();
	void testException();

public:
	int run();
};

int Application::run() {
	Fraction f1(3, 2);	// numerator=3, denominator=2 ("täljare"=3, "nämnare"=2)
	Fraction f2(10);	// numerator=10, denominator=1
	Fraction result;

	testUser();

	// Testing class Fraction with predefined values
	result = (1 + f1) * (f2 - 3);
	cout << "Following should output \"(1 + 3/2) * (10/1 - 3) = 35/2\", got: "
		<< result << endl;
	assert(result == Fraction(35, 2));

	test1();
	test2();

	testException();

	cout << "Press enter to continue...";
	readEnter();
	return 0;
}

// testing user input.
void Application::testUser() {
	Fraction f1(3, 2);
	Fraction f2(10);
	Fraction result;

	cout << "--begin user test--" << endl;
	readEnter();

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

void Application::test1() {
	Fraction result;

	cout << "--begin test1--" << endl;
	readEnter();

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

	cout << "--end test1--" << endl << endl;
}

void Application::test2() {
	Fraction result;

	cout << "--begin test2--" << endl;
	readEnter();

	result = 6 * Fraction(2, 7);
	cout << "Following should output \"6 * 2/7 = 12/7\", got: "
		<< result << endl;
	assert(result == Fraction(12, 7));

	result = 8 / Fraction(1, 4);
	cout << "Following should output \"8 / 1/4 = 32/1\", got: "
		<< result << endl;
	assert(result == Fraction(32, 1));

	result = 32 - Fraction(6, 3);
	cout << "Following should output \"32 - 6/3 = 30/1\", got: "
		<< result << endl;
	assert(result == Fraction(30, 1));

	result = 65 + Fraction(76, 56);
	cout << "Following should output \"65 + 76/56 = 929/14\", got: "
		<< result << endl;
	assert(result == Fraction(929, 14));

	cout << "--end test2--" << endl << endl;
}

void Application::testException() {
	Fraction result;
	bool thrown = false;

	cout << "--begin exception test--" << endl;
	readEnter();

	try {
		result = 0;
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 0\"? " << (thrown ? "yes" : "no") <<
		endl;
	assert(thrown);

	thrown = false;
	try {
		result = 5 - Fraction(5, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 5 - 5/1\"? " <<
		(thrown ? "yes" : "no") << endl;

	thrown = false;
	try {
		result = 1 - Fraction(3, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 1 - 3/1\"? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	cout << "--end exception test--" << endl << endl;
}

int main() {
	Application myApp;
	return myApp.run();
}
