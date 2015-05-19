/*
 * mediadbreader.h
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#ifndef MEDIADBREADER_H_
#define MEDIADBREADER_H_

#include <fstream>
#include <istream>

class BaseMedia;

class MediaDbReader {
	static const int ARTIST_NAME_MAX_LENGTH = 128;
	static const int ALBUM_NAME_MAX_LENGTH = 128;
	static const int YEAR_CHAR_MAX_LENGTH = 10;
	std::ifstream m_reader;

public:
	MediaDbReader(const char *a_filename) {
		open(a_filename);
	}

	void open(const char *filename);

	void close() {
		m_reader.close();
	}

	BaseMedia *readNext();
};

#endif /* MEDIADBREADER_H_ */
