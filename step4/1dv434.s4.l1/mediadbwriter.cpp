/*
 * mediadbwriter.cpp
 *
 *  Created on: 20 maj 2015
 *      Author: Zlatko Ladan
 */

#include <cstdlib>
#include "mediadbwriter.h"
#include "musicalbummedia.h"

using std::endl;
using std::invalid_argument;

// Gets a lower case version of the string.
char *MediaDbWriter::lowerer(const char *a_chr) {
	char *tmp = new char[strlen(a_chr) + 1], *j = NULL;

	j = tmp;
	for (const char *i = a_chr; *i; ++i, j++) {
		*j = tolower(*i);
	}

	*j = '\0';

	return tmp;
}

// Opens a file, closes if one is already opened.
void MediaDbWriter::open(const char *a_filename) {
	if (m_writer.is_open()) {
		close();
	}

	m_writer.open(a_filename);
}

// Writes a line of data.
// May throw invalid_argument if a_media is not MusicAlbumMedia,
// if a_media is NULL, or if an error occurs during the writing of the file.
void MediaDbWriter::writeNext(const BaseMedia *a_media) throw (invalid_argument) {
	if (a_media->getId() != MusicAlbumMedia::IDENTIFICATION) {
		throw invalid_argument("Only music album media is supported!");
	}

	if (a_media == NULL) {
		throw invalid_argument("a_media was null!");
	}

	MusicAlbumMedia *media = (MusicAlbumMedia *) a_media;

	char *tmpArtist = lowerer(media->getArtistName()), *tmpAlbum = lowerer(
			media->getAlbumName());

	m_writer << tmpArtist << DELIMITER << tmpAlbum << DELIMITER
			<< media->getReleaseYear() << endl;

	delete[] tmpArtist;
	delete[] tmpAlbum;

	if (!m_writer.good()) {
		throw invalid_argument("Something went wrong during writing of file!");
	}
}
