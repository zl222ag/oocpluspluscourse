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

void MediaDbWriter::open(const char *a_filename) {
	if (m_writer.is_open()) {
		close();
	}

	m_writer.open(a_filename);
}

void MediaDbWriter::writeNext(const BaseMedia *a_media) throw (invalid_argument) {
	if (a_media->getId() != MusicAlbumMedia::IDENTIFICATION) {
		throw invalid_argument("Only music album media is supported!");
	}

	MusicAlbumMedia *media = (MusicAlbumMedia *) a_media;

	m_writer << media->getArtistName() << DELIMITER << media->getAlbumName()
			<< DELIMITER << media->getReleaseYear() << endl;

	if (!m_writer.good()) {
		throw invalid_argument("Something went wrong during writing of file!");
	}
}
