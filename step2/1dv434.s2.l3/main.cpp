// 1dv434.s2.l3/main.cpp
// Datum: 2015-04-16
// Programmerare: Zlatko Ladan
// Kort beskrivning: Skapa klass som tar hand om br�ktal.

#include <iostream>
#include <inputoutput.h>
#include "fraction.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

class App {
public:
	App() {

	}

	~App() {
	}

	int run();
};

int App::run() {
	Fraction f1(3, 2); //  numerator = 3 ("t�ljare") , denominator = 2; ("n�mnare")
	Fraction f2(10); // numerator = 10, denominator = 1
	Fraction result;

	cout << "Test 1:" << endl; // Test med f�rdefinierade v�rden
	cout << "(1 + 3/2) * (10 - 3) = ";
	cout << (1 + f1) * (f2 - 3) << endl << endl; //  Ska skriva ut "35/2"

	cout << "Test 2:" << endl; // Test med anv�ndarens v�rden
	cout << "Input two fractions as example:  2 / - 3 5 / 6" << endl;
	cin >> f1 >> f2;

	result = f1 + f2;
	// Ska skriva ut: "2 / -3 + 5 / 6 = 1 / 6" om testfallet ovan anv�nts
	cout << endl << f1 << " + " << f2 << " = " << result << endl;
	result = f1 - f2;
	// Skas kriva ut : "2/ - 3 - 5 / 6 = - 3 / 2 " om testfallet ovan anv�nts
	cout << endl << f1 << " - " << f2 << " = " << result << endl;
	return EXIT_SUCCESS;
}

// Starts from the beginning.
int main() {
	App app;

	return app.run();
}
