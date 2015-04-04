#ifndef APP_H
#define APP_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "inputoutput.h"
#include "temperature.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::runtime_error;

class App {
private:
	static const int PRECISION = 2;
	static const int NUMBER_WIDTH = 8;
	static const int VALUES_PER_ROW = 6;
	static char *LOG_FILE /*= "templog.txt"*/;

	void outputValues(Temperature *);

public:
	int run();
};

#endif // APP_H
