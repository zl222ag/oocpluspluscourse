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

// Finds the specified media.
BaseMedia *MediaRegister::findMedia(const char *a_artistName,
		const char *a_albumName) const {
	vector<BaseMedia *>::const_iterator tmp = std::find_if(m_media.begin(),
			m_media.end(), [&](BaseMedia *a_media) {
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

// Saves register to file.
void MediaRegister::saveReg(const char *a_dbFile /* "media.dat" */) const
		throw (invalid_argument) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbWriter writer(a_dbFile);

	for (vector<BaseMedia *>::const_iterator i = m_media.begin();
			i != m_media.end(); ++i) {
		writer.writeNext(*i);
	}
}

// Loads register from file.
void MediaRegister::loadReg(const char *a_dbFile /* "media.dat" */)
		throw (invalid_argument) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbReader reader(a_dbFile);

	BaseMedia *media = NULL;

	while ((media = reader.readNext()) != NULL) {
		addMedia(media);
	}
}
