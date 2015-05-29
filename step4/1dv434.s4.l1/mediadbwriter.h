/*
 * mediadbwriter.h
 *
 *  Created on: 20 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef MEDIADBWRITER_H_
#define MEDIADBWRITER_H_

#include <fstream>
#include <stdexcept>
#include <cstring>

class BaseMedia;

class MediaDbWriter {
	static const char DELIMITER = '|';
	static const int YEAR_CHAR_MAX_LENGTH = 10;
	std::ofstream m_writer;

	// Gets a lower case version of the string.
	static char *lowerer(const char *a_chr);

public:
	MediaDbWriter() {
	}

	// Opens a file.
	MediaDbWriter(const char *a_filename) {
		open(a_filename);
	}

	~MediaDbWriter() throw(std::invalid_argument) {
		if (m_writer.is_open()) {
			close();
		}
	}

	// Opens a file, closes if one is already opened.
	// May throw invalid_argument if an error occured while opening the file.
	void open(const char *filename) throw (std::invalid_argument);

	// If a file currently opened.
	bool isOpened() {
		return m_writer.is_open();
	}

	// Closes a file (may throw invalid_argument if a file is not
	// already opened.
	void close() throw(std::invalid_argument);

	// Writes a line of data.
	// May throw invalid_argument if "media" is not MusicAlbumMedia or
	// if an error occurs during the writing of the file.
	void write(const BaseMedia &media) throw (std::invalid_argument);
};

#endif // MEDIADBWRITER_H_
