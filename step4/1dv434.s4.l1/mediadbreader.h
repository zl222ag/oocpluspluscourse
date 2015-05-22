/*
 * mediadbreader.h
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#ifndef MEDIADBREADER_H_
#define MEDIADBREADER_H_

#include <fstream>
#include <stdexcept>

class BaseMedia;

class MediaDbReader {
	static const char DELIMITER = '|';
	static const int ARTIST_NAME_MAX_LENGTH = 128, ALBUM_NAME_MAX_LENGTH = 128,
			YEAR_CHAR_MAX_LENGTH = 10;
	std::ifstream m_reader;

	void lowerer(char *a_chr) {
		for (char *i = a_chr; *i; ++i) {
			*i = tolower(*i);
		}
	}

public:
	MediaDbReader() {
	}

	MediaDbReader(const char *a_filename) {
		open(a_filename);
	}

	void open(const char *filename);

	void close() {
		m_reader.close();
	}

	// Returns a media (must be deleted),
	BaseMedia *readNext() throw (std::invalid_argument);
};

#endif /* MEDIADBREADER_H_ */
