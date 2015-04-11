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
	// Clears the console screen.
	static void clearScreen();

	// Ignores all user's input until the enter key is pressed.
	// source: http://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
	static void readEnter();

	// Reads the user's input (ignores all characters except the first).
	static void readChar(char &);
};

#endif // INPUT_OUTPUT_H
