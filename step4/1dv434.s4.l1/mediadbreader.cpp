/*
 * mediadbreader.cpp
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#include <cstdlib>
#include "mediadbreader.h"
#include "musicalbummedia.h"

void MediaDbReader::open(const char *a_filename) {
	if (m_reader.is_open()) {
		close();
	}

	m_reader.open(a_filename);
}

BaseMedia *MediaDbReader::readNext() {
	char *artist = new char[ARTIST_NAME_MAX_LENGTH],
		*album, *year;

	m_reader.getline(artist, ARTIST_NAME_MAX_LENGTH, '|');

	if (m_reader.gcount() < 1) {
		delete[] artist;
		return NULL;
	}

	album = new char[ALBUM_NAME_MAX_LENGTH];
	m_reader.getline(album, ALBUM_NAME_MAX_LENGTH, '|');

	if (m_reader.gcount() < 1) {
		delete[] artist;
		delete[] album;
		return NULL;
	}

	year = new char[YEAR_CHAR_MAX_LENGTH];
	m_reader.getline(year, YEAR_CHAR_MAX_LENGTH);

	if (m_reader.gcount() < 1) {
		delete[] artist;
		delete[] album;
		delete[] year;
		return NULL;
	}

	MusicAlbumMedia *s = new MusicAlbumMedia(artist, album,
			(short) std::atoi(year));

	delete[] artist;
	delete[] album;
	delete[] year;

	return (BaseMedia *) s;
}
