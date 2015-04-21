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
	void testFractionArithmetic();
	void testRightSideArithmetic();
	void testLeftSideArithmetic();
	void testBothSideArithmetic();
	void testException();

public:
	int run();
};

int Application::run() {
	Fraction f1(3, 2);	// numerator=3, denominator=2 ("täljare"=3, "nämnare"=2)
	Fraction f2(10);	// numerator=10, denominator=1
	Fraction result;

	testUser();
	testFractionArithmetic();

	// Testing class Fraction with predefined values
	result = (1 + f1) * (f2 - 3);
	cout << "Following should output \"(1 + 3/2) * (10/1 - 3) = 35/2\", got: "
		<< result << endl;
	assert(result == Fraction(35, 2));

	testLeftSideArithmetic();
	testRightSideArithmetic();
	testBothSideArithmetic();

	testException();

	cout << "Press enter to continue...";
	readEnter();
	return 0;
}

// Testing user input.
void Application::testUser() {
	Fraction f1, f2;
	bool tryAgain = false;
	cout << "--begin user test--" << endl;
	readEnter();

	cout << "Input two fractions as: 2/-3 5/6 "
		"(separated by whitespace):" << endl;

	do {
		try {
			cin >> f1;
			tryAgain = false;
		} catch (zero_division_error e) {
			cout << e.what() << endl;
			cout << "You'll have to write again!" << endl;
			InputOutput::readEnter();
			tryAgain = true;
		}
	} while (tryAgain);

	do {
		try {
			cin >> f2;
			tryAgain = false;
		} catch (zero_division_error e) {
			cout << e.what() << endl;
			cout << "You'll have to write again!" << endl;
			InputOutput::readEnter();
			tryAgain = true;
		}
	} while (tryAgain);

	cout << "Following should be \"2/-3\", got: " << f1 <<
		endl;
	assert(f1 == Fraction(2, -3));
	assert(Fraction(2, -3) == f1);

	cout << "Following should be \"5/6\" got: " << f2 <<
		endl;
	assert(f2 == Fraction(5, 6));
	assert(Fraction(5, 6) == f2);

	cout << "--end user test--" << endl << endl;
}

// Testing fraction with two Fraction classes.
void Application::testFractionArithmetic() {
	Fraction f1(2, -3), f2(5, 6), result;

	cout << "--begin fraction arithmetic test--" << endl;
	result = f1 + f2;
	cout << "Following should output \"2/-3 + 5/6 = 1/6\", got: " << result <<
		endl;
	assert(result == Fraction(1, 6));
	assert(Fraction(1, 6) == result);

	result = f1 - f2;
	cout << "Following should output \"2/-3 - 5/6 = -3/2\", got: " << result <<
		endl;
	assert(result == Fraction(-3, 2));
	assert(Fraction(-3, 2) == result);

	result = f1 * f2;
	cout << "Following should output \"2/-3 * 5/6 = -5/9\", got: " << result <<
		endl;
	assert(result == Fraction(-5, 9));
	assert(Fraction(-5, 9) == result);

	result = f1 / f2;
	cout << "Following should output \"2/-3 / 5/6 = -4/5\", got: " << result <<
		endl;
	assert(result == Fraction(-4, 5));
	assert(Fraction(-4, 5) == result);

	cout << "--end fraction arithmetic test--" << endl << endl;
}

// Testing fraction where numbers are on the right and fractions
// are on left side.
void Application::testRightSideArithmetic() {
	Fraction result;

	cout << "--begin right side arithmetic test--" << endl;
	readEnter();

	result = Fraction(5, 2) + 2;
	cout << "Following should output \"5/2 + 2 = 9/2\", got: "
		<< result << endl;
	assert(result == Fraction(9, 2));
	assert(Fraction(9, 2) == result);

	result = Fraction(9, 7) - 6;
	cout << "Following should output \"9/7 - 6 = -33/7\", got: "
		<< result << endl;
	assert(result == Fraction(-33, 7));
	assert(Fraction(-33, 7) == result);

	result = Fraction(3, 3) / 5;
	cout << "Following should output \"3/2 / 5 = 1/5\", got: "
		<< result << endl;
	assert(result == Fraction(1, 5));
	assert(Fraction(1, 5) == result);

	result = Fraction(7, 2) * 3;
	cout << "Following should output \"7/2 * 3 = 21/2\", got: "
		<< result << endl;
	assert(result == Fraction(21, 2));
	assert(Fraction(21, 2) == result);

	cout << "--end right side arithmetic test--" << endl << endl;
}

// Testing fraction where numbers are on the left and fractions
// are on right side.
void Application::testLeftSideArithmetic() {
	Fraction result;

	cout << "--begin left side arithmetic test--" << endl;
	readEnter();

	result = 6 * Fraction(2, 7);
	cout << "Following should output \"6 * 2/7 = 12/7\", got: "
		<< result << endl;
	assert(result == Fraction(12, 7));
	assert(Fraction(12, 7) == result);

	cout << "Following should output \"6 * 2/7 != 13/7\", got: "
		<< result << endl;
	assert(!(result == Fraction(13, 7)));
	assert(!(Fraction(13, 7) == result));
	assert(result != Fraction(13, 7));
	assert(Fraction(13, 7) != result);

	result = 8 / Fraction(1, 4);
	cout << "Following should output \"8 / 1/4 = 32/1\", got: "
		<< result << endl;
	assert(result == Fraction(32, 1));
	assert(Fraction(32, 1) == result);

	cout << "Following should output \"8 / 1/4 != 1/1\", got: "
		<< result << endl;
	assert(!(result == Fraction(1, 1)));
	assert(!(Fraction(1, 1) == result));
	assert(result != Fraction(1, 1));
	assert(Fraction(1, 1) != result);

	result = 32 - Fraction(6, 3);
	cout << "Following should output \"32 - 6/3 = 30/1\", got: "
		<< result << endl;
	assert(result == Fraction(30, 1));
	assert(Fraction(30, 1) == result);

	result = 65 + Fraction(76, 56);
	cout << "Following should output \"65 + 76/56 = 929/14\", got: "
		<< result << endl;
	assert(result == Fraction(929, 14));
	assert(Fraction(929, 14) == result);

	cout << "--end left side arithmetic test--" << endl << endl;
}

// Testing fraction where numbers are on the left and right, and fractions
// are in between.
void Application::testBothSideArithmetic() {
	Fraction result;

	cout << "--begin both side arithmetic test--" << endl;
	readEnter();

	result = 99 + Fraction(32, 6) + 99;
	cout << "Following should output \"99 + 32/6 + 99 = 610/3\", got: "
		<< result << endl;
	assert(result == Fraction(610, 3));
	assert(Fraction(610, 3) == result);

	result = 10 - Fraction(784, 3347) - 45;
	cout << "Following should output \"99 + 784/3347 + 99 = -117929/3347\", "
		"got: " << result << endl;
	assert(result == Fraction(-117929, 3347));
	assert(Fraction(-117929, 3347) == result);

	result = 6 / Fraction(2, 1) / 3;
	cout << "Following should output \"6 / 2/1 / 3 = 6/6\", got: "
		<< result << endl;
	assert(result == Fraction(6, 6));
	assert(Fraction(6, 6) == result);

	result = 100 * Fraction(34, 62) * 8;
	cout << "Following should output \"100 * 34/62 * 8 = 27200/62\", got: "
		<< result << endl;
	assert(result == Fraction(27200, 62));
	assert(Fraction(27200, 62) == result);



	result = 5 + Fraction(61, 3) * 2;
	cout << "Following should output \"5 + 61/3 * 2 = 137/3\", got: "
		<< result << endl;
	assert(result == Fraction(137, 3));
	assert(Fraction(137, 3) == result);

	result = 2 / Fraction(7, 2) * 3;
	cout << "Following should output \"2 / 7/2 * 3 = 21/1\", got: "
		<< result << endl;
	assert(result == Fraction(12, 7));
	assert(Fraction(12, 7) == result);

	result = 9 * Fraction(43, 4) - 90;
	cout << "Following should output \"9 * 43/4 - 90 = 27/4\", got: "
		<< result << endl;
	assert(result == Fraction(27, 4));
	assert(Fraction(27, 4) == result);

	cout << "--end both side arithmetic test--" << endl << endl;
}

// Testing exceptions for Fraction class
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
