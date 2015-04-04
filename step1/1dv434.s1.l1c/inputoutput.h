#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

class InputOutput {
public:
	static void clearScreen();
	static void readEnter();
	static void readChar(char &);
};

#endif // INPUT_OUTPUT_H
