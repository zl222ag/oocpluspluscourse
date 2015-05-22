/*
 * mediadbreader.cpp
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#include <cstdlib>
#include "mediadbreader.h"
#include "musicalbummedia.h"

using std::atoi;
using std::invalid_argument;

void MediaDbReader::open(const char *a_filename) {
	if (m_reader.is_open()) {
		close();
	}

	m_reader.open(a_filename);
}

BaseMedia *MediaDbReader::readNext() throw (invalid_argument) {
	if (!m_reader.is_open()) {
		throw invalid_argument("No file was opened!");
	}

	char *artist = new char[ARTIST_NAME_MAX_LENGTH], *album, *year;

	m_reader.getline(artist, ARTIST_NAME_MAX_LENGTH, DELIMITER);

	if (m_reader.gcount() < 1) {
		delete[] artist;

		return NULL;
	}

	lowerer(artist);

	album = new char[ALBUM_NAME_MAX_LENGTH];
	m_reader.getline(album, ALBUM_NAME_MAX_LENGTH, DELIMITER);

	if (m_reader.gcount() < 1) {
		delete[] artist;
		delete[] album;

		throw invalid_argument("Album name could not be read!");
	}

	lowerer(album);

	year = new char[YEAR_CHAR_MAX_LENGTH];
	m_reader.getline(year, YEAR_CHAR_MAX_LENGTH);

	if (m_reader.gcount() < 1) {
		delete[] artist;
		delete[] album;
		delete[] year;

		throw invalid_argument("Year could not be read!");
	}

	BaseMedia *tmp = new MusicAlbumMedia(artist, album, (short) atoi(year));

	delete[] artist;
	delete[] album;
	delete[] year;

	return tmp;
}
