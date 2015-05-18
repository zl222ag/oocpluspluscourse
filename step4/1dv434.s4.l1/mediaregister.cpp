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

void MediaRegister::saveReg() {

}

void MediaRegister::loadReg() {
	if (m_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbReader *reader = NULL;
	try {
		reader = new MediaDbReader(m_dbFile);
	} catch (...) {
		return;
	}
	BaseMedia *media = NULL;

	while ((media = reader->readNext()) != NULL) {
		addMedia(media);
	}
}
