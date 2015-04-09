#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <cstdio>
#include <fstream>
#include <stdexcept>
#include "filereader.h"

using std::ifstream;
using std::ios;
using std::runtime_error;
using std::out_of_range;

class Temperature {
public:
	const int MAX_ITEMS = 100;
	~Temperature();

	// Loads all temperatures from file.
	// Stops loading until reaching EOF or a non numeric character.
	// Removes old values.
	void LoadTemperatures(char *);

	// Gets the size.
	int getSize();

	// Gets a temperature value.
	// may throw out_of_range if out of range.
	double get(int);

	// Gets the max and min values.
	void getMaxMin(double &, double &);

	// Gets the mean values.
	double getMean();

private:
	int m_size = 0;
	double *m_items = NULL;

	// Removes all temperatures (if there are any).
	void deleteTemperatures();
};

#endif // TEMPERATURE_H
