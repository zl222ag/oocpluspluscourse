/*
 * mediaregister.cpp
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <compare.h>
#include "mediaregister.h"
#include "basemedia.h"
#include "mediadbreader.h"
#include "mediadbwriter.h"

using std::vector;
using std::invalid_argument;

void MediaRegister::saveReg(const char *a_dbFile /* "media.dat" */) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbWriter *writer = NULL;

	try {
		writer = new MediaDbWriter(a_dbFile);
	} catch (...) {
		return;
	}

	for (vector<BaseMedia *>::iterator i = m_media.begin(); i != m_media.end();
		++i) {
		writer->writeNext(*i);
	}
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

BaseMedia *MediaRegister::findMedia(const char *a_artistName, const char *a_albumName) {
	vector<BaseMedia *>::iterator tmp =
		std::find_if(m_media.begin(), m_media.end(), [&](BaseMedia *a_media) {
		if (a_media->getId() != MusicAlbumMedia::IDENTIFICATION) {
			return false;
		}

		MusicAlbumMedia *data = (MusicAlbumMedia *) a_media;

		return Compare::equali(a_artistName, data->getArtistName()) &&
			Compare::equali(a_albumName, data->getAlbumName());
	});

	// No such item found.
	if (tmp == m_media.end()) {
		return NULL;
	}

	return *tmp;
}
