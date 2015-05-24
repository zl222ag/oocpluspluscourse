/*
 * musicalbummedia.cpp
 *
 *  Created on: 15 maj 2015
 *      Author: zlatko
 */

#include <stdexcept>
#include "musicalbummedia.h"

// The copy constructor.
// c++11 supports this (delagating constructor)!
MusicAlbumMedia::MusicAlbumMedia(const MusicAlbumMedia &a_media) :
		MusicAlbumMedia(a_media.m_artistName, a_media.m_albumName,
				a_media.m_releaseYear) {
}

// "Normal" constructor.
// May throw invalid_argument if one parameter is NULL.
MusicAlbumMedia::MusicAlbumMedia(const char *a_artistName,
		const char *a_albumName, short a_releaseYear)
				throw (std::invalid_argument) :
		m_releaseYear(a_releaseYear) {
	setArtistName(a_artistName);
	setAlbumName(a_albumName);
}

// The artist's name.
// Makes copy.
// May throw invalid_argument if artistName is NULL.
void MusicAlbumMedia::setArtistName(const char *a_artistName)
		throw (std::invalid_argument) {
	if (a_artistName == NULL) {
		throw std::invalid_argument("Artist name cannot be NULL!");
	}

	strcpy(m_artistName, a_artistName);
}

// The album name.
// Makes copy.
// May throw invalid_argument if albumName is NULL.
void MusicAlbumMedia::setAlbumName(const char *a_albumName)
		throw (std::invalid_argument) {
	if (a_albumName == NULL) {
		throw std::invalid_argument("Album name cannot be NULL!");
	}

	strcpy(m_albumName, a_albumName);
}

// Needed when not an initialization, but assignment.
MusicAlbumMedia MusicAlbumMedia::operator=(const MusicAlbumMedia &a_media) {
	setArtistName(a_media.m_artistName);
	setAlbumName(a_media.m_albumName);
	m_releaseYear = a_media.m_releaseYear;
	return *this;
}

// Normal operator (from base).
bool MusicAlbumMedia::operator==(const BaseMedia &a_other) const {
	if (getId() != a_other.getId()) {
		return false;
	}

	// Calls other non-base operator
	return *this == *(MusicAlbumMedia *) &a_other;
}

// Normal operator (from base).
bool MusicAlbumMedia::operator!=(const BaseMedia &a_other) const {
	if (getId() != a_other.getId()) {
		return false;
	}

	// Calls other non-base operator
	return *this != *(MusicAlbumMedia *) &a_other;
}

// Sorts by the artist's name, then its album name.
bool MusicAlbumMedia::operator<(const MusicAlbumMedia &a_other) const {
	int nameVal = strcmp(m_artistName, a_other.m_artistName);

	if (nameVal != 0) {
		return nameVal < 0;
	}

	return strcmp(m_albumName, a_other.m_albumName) < 0;
}

// Sorts by the artist's name, then its album name (if same class).
bool MusicAlbumMedia::operator<(const BaseMedia &a_other) const {
	if (getId() != a_other.getId()) {
		return false;
	}

	// Calls other non-base operator
	return *this < *(MusicAlbumMedia *) &a_other;
}
