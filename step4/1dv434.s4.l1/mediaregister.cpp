/*
 * mediaregister.cpp
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#include <list>
#include <algorithm>
#include <stdexcept>
#include <compare.h>
#include "mediaregister.h"
#include "basemedia.h"
#include "mediadbreader.h"
#include "mediadbwriter.h"

using std::list;
using std::invalid_argument;

// Adds media!
// May throw invalid_argument if a_media has already been added.
void MediaRegister::addMedia(const BaseMedia &a_media) throw (invalid_argument) {
	if (a_media.getId() == MusicAlbumMedia::IDENTIFICATION) {
		// MusicAlbumMedia
		const MusicAlbumMedia media = *((MusicAlbumMedia *) &a_media);
		BaseMedia *tmp;

		if ((tmp = findMedia(media.getArtistName(), media.getAlbumName())) != NULL) {
			delete tmp;
			throw invalid_argument("That media has already been added!");
		}
	} else {
		// Other media
		if (find_if(m_media.begin(), m_media.end(), [&a_media](BaseMedia *a_current) {
			return a_media == *a_current;
		}) != m_media.end()) {
			throw invalid_argument("That media has already been added!");
		}
	}

	m_media.push_back(a_media.clone());
}

// Removes a media!
bool MediaRegister::removeMedia(const BaseMedia &a_media) {
	bool retVal = false;
	m_media.remove_if(
		[&retVal, &a_media](BaseMedia *a_current) {
				if (*a_current == a_media) {
					delete a_current;
					retVal = true;
					return true;
				}

				return false;
			});

	return retVal;
}

// Finds the specified media by artist name and album name.
// May return NULL if the specified media was not found.
BaseMedia *MediaRegister::findMedia(const char *a_artistName,
		const char *a_albumName) const {
	list<BaseMedia *>::const_iterator tmp = std::find_if(m_media.begin(),
			m_media.end(), [a_artistName, a_albumName](BaseMedia *a_media) {
				if (a_media->getId() != MusicAlbumMedia::IDENTIFICATION) {
					return false;
				}

				const MusicAlbumMedia data = *((MusicAlbumMedia *) a_media);

				return Compare::equali(a_artistName, data.getArtistName()) &&
				Compare::equali(a_albumName, data.getAlbumName());
			});

	// Return NULL if not found!
	return ((tmp == m_media.end()) ? NULL : (*tmp)->clone());
}

// Finds the specified media's by artist's name.
list<BaseMedia *> MediaRegister::findMedia(const char *a_artistName) const {
	list<BaseMedia *>::const_iterator tmp, pos = m_media.begin();
	list<BaseMedia *> out;

	while ((tmp =
			std::find_if(pos, m_media.end(),
					[a_artistName](BaseMedia *a_media) {
						if (a_media->getId() !=
								MusicAlbumMedia::IDENTIFICATION) {
							return false;
						}

						return Compare::equali(a_artistName,
								((MusicAlbumMedia *) a_media)->getArtistName());
					})) != m_media.end()) {
		out.push_back((*tmp)->clone());

		if (tmp != m_media.end()) {
			pos = tmp; // + 1 is not possible
			++pos;
		}
	}

	return out;
}

// Replaces media
// May throw invalid_argument if a_media has already been added.
bool MediaRegister::replaceMedia(const BaseMedia &a_from,
	const BaseMedia &a_to) {
	if (a_to.getId() == MusicAlbumMedia::IDENTIFICATION) {
		// MusicAlbumMedia
		const MusicAlbumMedia media = *((MusicAlbumMedia *) &a_to);
		BaseMedia *tmp;

		if ((tmp = findMedia(media.getArtistName(), media.getAlbumName())) != NULL) {
			delete tmp;
			throw invalid_argument("That media has already been added!");
		}
	} else {
		// Other media
		if (find_if(m_media.begin(), m_media.end(), [&a_to](BaseMedia *a_current) {
			return a_to == *a_current;
		}) != m_media.end()) {
			throw invalid_argument("That media has already been added!");
		}
	}

	for (std::list<BaseMedia*>::iterator i = m_media.begin();
			i != m_media.end(); ++i) {
		if (**i == a_from) {
			delete *i;
			*i = a_to.clone();
			return true;
		}
	}

	return false;
}

// Saves register to file.
// May throw invalid_argument if a_dbFile is NULL.
void MediaRegister::saveReg(const char *a_dbFile /* "media.dat" */) const
		throw (invalid_argument) {
	if (a_dbFile == NULL) {
		throw invalid_argument("The database filename cannot be NULL!");
	}

	MediaDbWriter writer(a_dbFile);

	for (list<BaseMedia *>::const_iterator i = m_media.begin();
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
		try {
			addMedia(*media);
		} catch (const invalid_argument &) {
			std::clog << "\"" << *media << "\" was already added!" << std::endl;
		}

		delete media;
	}
}
