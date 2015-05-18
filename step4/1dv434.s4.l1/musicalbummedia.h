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
#include "basemedia.h"

class MusicAlbumMedia : BaseMedia {
	char *m_artistName, *m_albumName;
	short m_releaseYear;

public:
	MusicAlbumMedia() :
		m_artistName(NULL), m_albumName(NULL), m_releaseYear(0) {
	}

	MusicAlbumMedia(const char *a_artistName, const char *a_albumName,
			short a_releaseYear) :
				m_releaseYear(a_releaseYear) {
		m_artistName = new char[strlen(a_artistName) + 1];
		strcpy(m_artistName, a_artistName);

		m_albumName = new char[strlen(a_albumName) + 1];
		strcpy(m_albumName, a_albumName);
	}

	virtual ~MusicAlbumMedia() {
		if (m_artistName != NULL) {
			delete m_artistName;
		}

		if (m_albumName != NULL) {
			delete m_albumName;
		}
	}

	virtual void show() const {
		std::cout << "Artist: " << m_artistName << ", album: " << m_albumName <<
			", released: " << m_releaseYear << '.' << std::endl;
	}

	virtual int getId() const {
		return 0;
	}

	bool operator==(const MusicAlbumMedia &a_other) const {
		return getId() == a_other.getId();
	}

	// Sorts by the artist's name, then its album name.
	bool operator<(const MusicAlbumMedia &a_other) const {
		int nameVal = strcmp(m_artistName, a_other.m_artistName);

		if (nameVal != 0) {
			return nameVal < 0;
		}

		return strcmp(m_albumName, a_other.m_albumName) < 0;
	}
};

#endif /* MUSICALBUMMEDIA_H_ */
