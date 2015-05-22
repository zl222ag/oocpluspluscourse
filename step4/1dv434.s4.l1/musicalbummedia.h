/*
 * musicalbummedia.h
 *
 *  Created on: 15 maj 2015
 *      Author: zlatko
 */

#ifndef MUSICALBUMMEDIA_H_
#define MUSICALBUMMEDIA_H_

#include <cstdio>
#include <cstring>
#include <iostream>
#include <compare.h>
#include "basemedia.h"

class MusicAlbumMedia: public BaseMedia {
	char *m_artistName, *m_albumName;
	short m_releaseYear;

	// For output with cout or a file. Is used by friend std::operator
	// (base class).
	virtual std::ostream &print(std::ostream &a_ostream) const {
		return a_ostream << "Artist: " << m_artistName << ", album: "
				<< m_albumName << ", released: " << m_releaseYear << '.';
	}

public:
	static const int IDENTIFICATION = 10654;

	// C++ STL's require this.
	MusicAlbumMedia() :
			m_artistName(NULL), m_albumName(NULL), m_releaseYear(0) {
	}

	// The copy constructor.
	MusicAlbumMedia(const MusicAlbumMedia &a_media);

	// "Normal" constructor.
	MusicAlbumMedia(const char *artistName, const char *albumName,
			short releaseYear);

	// Removal.
	virtual ~MusicAlbumMedia() {
		if (m_artistName != NULL) {
			delete[] m_artistName;
		}

		if (m_albumName != NULL) {
			delete[] m_albumName;
		}
	}

	// The class's id (polymorhism).
	virtual int getId() const {
		return IDENTIFICATION;
	}

	// The artist's name.
	// Do not delete.
	const char *getArtistName() const {
		return m_artistName;
	}

	// The album name.
	// Do not delete.
	const char *getAlbumName() const {
		return m_albumName;
	}

	// Year the album got released.
	const short getReleaseYear() const {
		return m_releaseYear;
	}

	// Needed when not an initialization, but assignment.
	MusicAlbumMedia operator=(const MusicAlbumMedia &a_media);

	// Normal operator
	bool operator==(const MusicAlbumMedia &a_other) const {
		return Compare::equali(m_artistName, a_other.m_artistName)
				&& Compare::equali(m_albumName, a_other.m_albumName)
				&& m_releaseYear == a_other.m_releaseYear;
	}

	// Normal operator
	bool operator!=(const MusicAlbumMedia &a_other) const {
		return !Compare::equali(m_artistName, a_other.m_artistName)
				|| !Compare::equali(m_albumName, a_other.m_albumName)
				|| m_releaseYear != a_other.m_releaseYear;
	}

	// Normal operator (from base).
	virtual bool operator==(const BaseMedia &a_other) const {
		if (getId() != a_other.getId()) {
			return false;
		}

		// Calls other non-base operator
		return *this == *(MusicAlbumMedia *) &a_other;
	}

	// Normal operator (from base).
	virtual bool operator!=(const BaseMedia &a_other) const {
		if (getId() != a_other.getId()) {
			return false;
		}

		// Calls other non-base operator
		return *this != *(MusicAlbumMedia *) &a_other;
	}

	// Sorts by the artist's name, then its album name.
	bool operator<(const MusicAlbumMedia &a_other) const {
		int nameVal = strcmp(m_artistName, a_other.m_artistName);

		if (nameVal != 0) {
			return nameVal < 0;
		}

		return strcmp(m_albumName, a_other.m_albumName) < 0;
	}

	// Sorts by the artist's name, then its album name (if same class).
	virtual bool operator<(const BaseMedia &a_other) const {
		if (getId() != a_other.getId()) {
			return false;
		}

		// Calls other non-base operator
		return *this < *(MusicAlbumMedia *) &a_other;
	}
};

#endif /* MUSICALBUMMEDIA_H_ */
