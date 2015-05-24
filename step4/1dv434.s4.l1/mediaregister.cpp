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

// Finds the specified media by artist name and album name.
// May return NULL if the specified media was not found.
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

	// Return null if not found!
	return ((tmp == m_media.end()) ? NULL : *tmp);
}

// Finds the specified media's by artist's name.
vector<BaseMedia *> MediaRegister::findMedia(const char *a_artistName) const {
	vector<BaseMedia *>::const_iterator tmp, pos = m_media.begin();
	vector<BaseMedia *> out;

	while ((tmp = std::find_if(pos, m_media.end(), [&](BaseMedia *a_media) {
		if (a_media->getId() !=
				MusicAlbumMedia::IDENTIFICATION) {
			return false;
		}

		return Compare::equali(a_artistName,
				((MusicAlbumMedia *) a_media)->getArtistName());
	})) != m_media.end()) {
		out.push_back(*tmp);

		if (tmp != m_media.end()) {
			pos = tmp + 1;
		}
	}

	return out;
}

// Saves register to file.
// May throw invalid_argument if a_dbFile is NULL.
void MediaRegister::saveReg(const char *a_dbFile /* "media.dat" */) const
		throw (invalid_argument) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbWriter writer(a_dbFile);

	for (vector<BaseMedia *>::const_iterator i = m_media.begin();
			i != m_media.end(); ++i) {
		writer.write(*i);
	}
}

// Loads register from file.
// May throw invalid_argument if a_dbFile is NULL or
// if an error occurs during the reading of the file.
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
