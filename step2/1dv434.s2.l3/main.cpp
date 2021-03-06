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
//			2015-04-19  Update Version 2.0 by Zlatko Ladan.
/*************************************************************************/

#include <iostream>
#include <cassert>
#include <inputoutput.h>
#include "fraction.h"

using std::endl;
using std::cin;
using std::cout;

class Application {
	//asks the user to press enter, this function reads, ignores util enter is
	// typed.
	void readEnter() {
		cout << "Press enter to continue...";
		InputOutput::readEnter();
	}

	// Asks the user to write fraction.
	void userEnterFraction(Fraction &);
	// Testing user input. Manually.
	// Is the test that came from Test2_3.cpp.
	void testUserOldTest();
	// Testing fraction with two Fraction classes.
	void testFractionArithmetic();
	// Testing fraction where numbers are on the right and fractions
	// are on left side.
	void testRightSideArithmetic();
	// Testing fraction where numbers are on the left and fractions
	// are on right side.
	void testLeftSideArithmetic();
	// Testing fraction where numbers are on the left and right, and fractions
	// are in between.
	void testBothSideArithmetic();
	// Testing exceptions for Fraction class.
	void testException();
	// Testing "==" and "!=" operators for integer and Fraction comparison.
	void testInteger();

public:
	int run();
};

int Application::run() {
	testUserOldTest();

	testFractionArithmetic();

	testLeftSideArithmetic();
	testRightSideArithmetic();
	testBothSideArithmetic();

	testException();
	testInteger();

	readEnter();

	return 0;
}

// Asks the user to write fraction.
void Application::userEnterFraction(Fraction &a_f) {
	bool tryAgain = true;

	do {
		try {
			cin >> a_f;
			tryAgain = false;
		} catch (zero_division_error e) {
			cout << e.what() << endl;
			cout << "You'll have to write again!" << endl;
			readEnter();
			tryAgain = true;
		}
	} while (tryAgain);
}

// Testing user input. Manually.
// Is the test that came from Test2_3.cpp.
void Application::testUserOldTest() {
	Fraction f1(3, 2);	// numerator=3, denominator=2 ("t�ljare"=3, "n�mnare"=2)
	Fraction f2(10);	// numerator=10, denominator=1
	Fraction result;
	cout << "--begin user test--" << endl;
	readEnter();


	// Testing class Fraction with predefined values
	cout << "Test 1:" << endl;
	cout << "(1 + 3/2) * (10 - 3) = ";

	cout << (1 + f1) * (f2 - 3) << endl << endl;	// Should print "35/2"

	// Will test arithmetic operations between two fractions, entered by the user
	cout << "Test 2:" << endl;
	cout << "Input two fractions as example: 2/-3 5/6 (separated by whitespace):" << endl;

	// these two replaced "cin >> f1 >> f2;"
	userEnterFraction(f1);
	userEnterFraction(f2);

	result = f1 + f2;
	// Following should output "2/-3 + 5/6 = 1/6" if test case examples was used
	cout << endl << f1 << " + " << f2 << " = " << result << endl;

	result = f1 - f2;
	// Following should output "2/-3 - 5/6 = -3/2" if test case examples was used
	cout << endl << f1 << " - " << f2 << " = " << result << endl;

	result = f1 * f2;
	// Following should output "2/-3 * 5/6 = -5/9" if test case examples was used
	cout << endl << f1 << " * " << f2 << " = " << result << endl;

	// This part was modified to protect agains zero division.
	try {
		result = f1 / f2;
		// Following should output "2/-3 / 5/6 = -4/5" if test case examples was used
		cout << endl << f1 << " / " << f2 << " = " << result << endl;
	} catch (zero_division_error) {
		// Necessary if the user inputs values which can crash the application.
		cout << endl << f1 << " / " << f2 << " = zero division error!" << endl;
	}
	cout << "--end user test--" << endl << endl;
}

// Testing fraction with two Fraction classes.
void Application::testFractionArithmetic() {
	Fraction f1(2, -3), f2(5, 6), result;

	cout << "--begin fraction arithmetic test--" << endl;
	readEnter();

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
	assert(Fraction(18, 4) == result);
	assert(Fraction(2, 9) != result);
	assert(!(Fraction(2, 9) == result));

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
	cout << "Following should output \"7/2 * 3 = 42/4\", got: "
		<< result << endl;
	assert(result == Fraction(42, 4));
	assert(Fraction(42, 4) == result);
	assert(!(Fraction(42, 4) != result));

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
	assert(!(Fraction(32, 1) != result));

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
	assert(!(Fraction(929, 14) != result));

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

	// reverse, mixed!

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

// Testing exceptions for Fraction class.
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
	cout << "Threw exception on \"result = 0\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = 5 - Fraction(5, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 5 - 5/1\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = Fraction(5, 1) - Fraction(5, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 5/1 - 5/1\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = Fraction(676, 1) / Fraction(0, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 676/1 / 0/1\" (should)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(thrown);

	thrown = false;
	try {
		result = Fraction(0, 1) / Fraction(676, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 0/1 / 676/32\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = 1 - Fraction(3, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 1 - 3/1\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = Fraction(1, 0);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 1/0\" (should)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(thrown);

	thrown = false;
	try {
		result = Fraction(99, 0);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 99/0\" (should)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(thrown);

	thrown = false;
	try {
		result = Fraction(1, 1);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 1/1\" (should not)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(!thrown);

	thrown = false;
	try {
		result = Fraction(0, 0);
	} catch (zero_division_error) {
		thrown = true;
	}
	cout << "Threw exception on \"result = 0/0\" (should)? " <<
		(thrown ? "yes" : "no") << endl;
	assert(thrown);

	cout << "--end exception test--" << endl << endl;
}

// Testing "==" and "!=" operators for integer and Fraction comparison.
void Application::testInteger() {
	Fraction result;

	cout << "--begin integer test--" << endl;
	readEnter();

	result = 1;
	cout << "Following should output \"1 = 1/1\", got: "
		<< result << endl;
	assert(result == Fraction());
	assert(result == Fraction(1, 1));
	assert(result == Fraction(1));
	assert(result != Fraction(1, 2));
	assert(!(result == Fraction(1, 2)));
	assert(!(2 == result));
	assert(2 != result);
	assert(result != 2);

	result = 2;
	cout << "Following should output \"2 = 2/1\", got: "
		<< result << endl;
	assert(result == Fraction(2, 1));
	assert(result == Fraction(2));
	assert(result != Fraction(2, 2));
	assert(!(result == Fraction(2, 2)));
	assert(!(1 == result));
	assert(result == 2);
	assert(2 == result);
	assert(!(2 != result));
	assert(!(result != 2));

	result = -9;
	cout << "Following should output \"-9 = -9/1\", got: "
		<< result << endl;
	assert(result == Fraction(-9, 1));
	assert(result == Fraction(-9));
	assert(result != Fraction(-9, 2));
	assert(!(result == Fraction(-9, 2)));
	assert(!(9 == result));
	assert(result == -9);
	assert(-9 == result);
	assert(!(result != -9));
	assert(!(-9 != result));

	cout << "--end integer test--" << endl << endl;
}

int main() {
	Application myApp;
	return myApp.run();
}
