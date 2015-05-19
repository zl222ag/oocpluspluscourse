/*
 * mediaregister.cpp
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "mediaregister.h"
#include "basemedia.h"
#include "mediadbreader.h"

using std::vector;
using std::invalid_argument;

void MediaRegister::saveReg(const char *a_dbFile /* "media.dat" */) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}
	//TODO ADD MORE CONTENT!!!
}

void MediaRegister::loadReg(const char *a_dbFile /* "media.dat" */) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbReader *reader = NULL;

	try {
		reader = new MediaDbReader(a_dbFile);
	} catch (...) { // TODO CATCH PROPERLY!!!
		return;
	}

	BaseMedia *media = NULL;

	while ((media = reader->readNext()) != NULL) {
		addMedia(media);
	}
}
