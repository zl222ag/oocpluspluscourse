#ifndef INPUT_OUTPUT_CPP
#define INPUT_OUTPUT_CPP

#include <iostream>
#include <limits>
#include "inputoutput.h"

// Clears the console screen.
void InputOutput::clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
	// FIXME: DEFAULT cmd.exe built command, should probably be replaced.
	system("cls");
#elif defined(unix)
	// ANSI THINGY, clears the screen and set the cursor position at the
	// beginning!
	cout << "\033[2J\033[0f" << endl;
#endif
}

// Ignores all user's input until the enter key is pressed.
// source: http://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
void InputOutput::readEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads the user's input (ignores all characters except the first).
void InputOutput::readChar(char &a_userChoice) {
	cin.get(a_userChoice);
	readEnter();
}

#endif // INPUT_OUTPUT_CPP
