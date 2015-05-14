/*
 * mediaregister.cpp
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */
#include <stdexcept>
#include "mediaregister.h"
#include "basemedia.h"
#include "mediadbreader.h"

using std::invalid_argument;

void MediaRegister::addMedia(BaseMedia a_media) {
	if (findMedia() == NULL) { // TODO FIX THIS!!!
		throw NULL; // TODO FIX THIS TOO!!!
	}

	m_media.push_back(a_media);
}

void MediaRegister::removeMedia(const BaseMedia &a_media) {

}

void MediaRegister::saveReg() {

}

void MediaRegister::loadReg() {
	if (m_dbFile == NULL) {
		return;
	}

	MediaDbReader reader(m_dbFile);
}
