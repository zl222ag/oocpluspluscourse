#ifndef TEMPERATURE_CPP
#define TEMPERATURE_CPP

#include "temperature.h"

Temperature::~Temperature() {
	if (m_items != NULL) {
		delete[] m_items;
	}
}

// Loads all temperatures from file.
// Stops loading until reaching EOF or a non numeric character.
void Temperature::LoadTemperatures(char *a_filename) {
	double *tempItems = new double[MAX_ITEMS];
	int i;
	FileReader inputFile;

	inputFile.open(a_filename);

	for (i = 0; i < MAX_ITEMS; ++i) {
		if (!inputFile.readNextDouble(tempItems[i])) {
			break;
		}
	}

	inputFile.close();
	m_size = i;

	if ((double) m_size >(double) MAX_ITEMS / 2.0) {
		m_items = tempItems;
		return;
	}

	m_items = new double[m_size];

	for (i = 0; i < m_size; ++i) {
		m_items[i] = tempItems[i];
	}

	delete[] tempItems;
}

// Gets the size.
int Temperature::getSize() {
	return m_size;
}

// Gets a temperature value.
double Temperature::get(int a_index) {
	if (a_index < 0 || a_index > m_size) {
		throw out_of_range("Out of range for items!");
	}
	return m_items[a_index];
}

// Gets the max and min values.
void Temperature::getMaxMin(double &a_max, double &a_min) {
	a_max = a_min = m_items[0];

	for (int i = 1; i < m_size; ++i) {
		if (m_items[i] > a_max) {
			a_max = m_items[i];
		}
		if (m_items[i] < a_min) {
			a_min = m_items[i];
		}
	}
}

// Gets the mean values.
double Temperature::getMean() {
	double total = 0.0;

	for (int i = 0; i < m_size; ++i) {
		total += m_items[i];
	}

	return total / (double) m_size;
}

#endif // TEMPERATURE_CPP
