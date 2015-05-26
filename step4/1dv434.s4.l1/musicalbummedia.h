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
#include <stdexcept>
#include <compare.h>
#include "basemedia.h"

class MusicAlbumMedia: public BaseMedia {
public:
	static const int IDENTIFICATION = 10654;
	static const int CHARS_LIMIT = 128;

	// C++ STL's require this.
	// C++11 supports this (delegating constructors).
	MusicAlbumMedia() :
			MusicAlbumMedia("", "", 0) {
	}

	// The copy constructor.
	// c++11 supports this (delagating constructor)!
	MusicAlbumMedia(const MusicAlbumMedia &a_media) :
			MusicAlbumMedia(a_media.m_artistName, a_media.m_albumName,
					a_media.m_releaseYear) {
	}

	// "Normal" constructor.
	// May throw invalid_argument if one parameter is NULL.
	MusicAlbumMedia(const char *artistName, const char *albumName,
			short releaseYear) throw (std::invalid_argument);

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
	short getReleaseYear() const {
		return m_releaseYear;
	}

	// The artist's name.
	// Makes copy.
	// May throw invalid_argument if artistName is NULL.
	void setArtistName(const char *artistName) throw (std::invalid_argument);

	// The album name.
	// Makes copy.
	// May throw invalid_argument if albumName is NULL.
	void setAlbumName(const char *a_albumName) throw (std::invalid_argument);

	// Year the album got released.
	void setReleaseYear(short a_value) {
		m_releaseYear = a_value;
	}

	// Needed when not an initialization, but assignment.
	MusicAlbumMedia operator=(const MusicAlbumMedia &);

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
	virtual bool operator==(const BaseMedia &) const;

	// Normal operator (from base).
	virtual bool operator!=(const BaseMedia &) const;

	// Sorts by the artist's name, then its album name.
	bool operator<(const MusicAlbumMedia &) const;

	// Sorts by the artist's name, then its album name (if same class).
	virtual bool operator<(const BaseMedia &) const;

	// Cloning function derived from base class
	virtual MusicAlbumMedia *clone() const {
		return new MusicAlbumMedia(*this);
	}

private:
	char m_artistName[CHARS_LIMIT], m_albumName[CHARS_LIMIT];
	short m_releaseYear;

	// For output with cout or a file. Is used by friend std::operator
	// (base class).
	virtual std::ostream &print(std::ostream &a_ostream) const {
		return a_ostream << "Artist: " << m_artistName << ", album: "
				<< m_albumName << ", released: " << m_releaseYear << '.';
	}
};

#endif /* MUSICALBUMMEDIA_H_ */
