#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <iostream>
#include <limits>
#include <stdexcept>

class InputOutput {
public:
	// Clears the console screen.
	static void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
		// FIXME: DEFAULT cmd.exe built command, should probably be replaced.
		system("cls");
#elif defined(__unix__)
		// ANSI THINGY, clears the screen and set the cursor position at the
		// beginning!
		std::cout << "\033[2J\033[0;0f";
#endif
	}

	// Ignores all user's input until the enter key is pressed.
	// source: http://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
	static void readEnter() {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// Reads the user's input (ignores all characters except the first).
	static void readChar(char &a_userChoice) {
		std::cin.get(a_userChoice);
		readEnter();
	}

	// Reads a number from the user (repeated until it's not an error).
	static void readInteger(const char *text, int &value, int min,
			const char *lowErr = NULL, const char *miscError = NULL);

	// Reads a number from the user (repeated until it's not an error).
	// May throw runtime_error if min is greater than max
	static void readInteger(const char *text, int &value, int min, int max,
			const char *lowErr = NULL, const char *highErr = NULL,
			const char *miscError = NULL)
			throw (std::runtime_error);
};

#endif // INPUT_OUTPUT_H
