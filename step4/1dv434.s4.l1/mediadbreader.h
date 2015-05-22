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

	static void lowerer(char *a_chr) {
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

	// Opens a file, closes if one is already opened.
	void open(const char *filename);

	// If a file currently opened.
	bool isOpened() {
		return m_reader.is_open();
	}

	// Closes a file
	void close() {
		if (!m_reader.is_open()) {
			throw std::invalid_argument("No file was opened!");
		}

		m_reader.close();
	}

	// Reads next line that has data, returns NULL otherwise.
	// May throw invalid_argument if no file is opened, or
	// if album name or release year could not be read.
	BaseMedia *readNext() throw (std::invalid_argument);
};

#endif /* MEDIADBREADER_H_ */
