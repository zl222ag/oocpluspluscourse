/*
 * musicalbummedia.cpp
 *
 *  Created on: 15 maj 2015
 *      Author: zlatko
 */

#include "musicalbummedia.h"

MusicAlbumMedia::MusicAlbumMedia(const char *a_artistName,
	const char *a_albumName, short a_releaseYear) :
	m_releaseYear(a_releaseYear) {
	if (a_artistName != NULL) {
		m_artistName = new char[strlen(a_artistName) + 1];
		strcpy(m_artistName, a_artistName);
	}

	if (a_artistName != NULL) {
		m_albumName = new char[strlen(a_albumName) + 1];
		strcpy(m_albumName, a_albumName);
	}
}

// c++11 supports this!
MusicAlbumMedia::MusicAlbumMedia(const MusicAlbumMedia &a_media) :
		MusicAlbumMedia(a_media.m_artistName, a_media.m_albumName,
		a_media.m_releaseYear) {
}

MusicAlbumMedia MusicAlbumMedia::operator=(const MusicAlbumMedia &a_media) {
	if (m_artistName != NULL) {
		delete[] m_artistName;
		m_artistName = NULL;
	}

	if (m_albumName != NULL) {
		delete[] m_albumName;
		m_albumName = NULL;
	}

	if (a_media.m_artistName != NULL) {
		m_artistName = new char[strlen(m_artistName) + 1];
		m_artistName = a_media.m_artistName;
	}

	if (a_media.m_albumName != NULL) {
		m_albumName = new char[strlen(m_albumName) + 1];
		m_albumName = a_media.m_albumName;
	}

	return *this;
}