/*
 * mediadbreader.cpp
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#include <cstdlib>
#include <fstream>
#include "mediadbreader.h"
#include "basemedia.h"

void MediaDbReader::open(const char *a_filename) {
	if (m_reader.is_open()) {
		close();
	}

	m_reader.open(a_filename);
}

BaseMedia *MediaDbReader::read() {
	return NULL;
}
