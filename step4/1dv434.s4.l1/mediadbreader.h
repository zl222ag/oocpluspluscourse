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
	static const int YEAR_CHAR_MAX_LENGTH = 10;
	std::ifstream m_reader;

	// Makes a string lowercase.
	static void lowerer(char *a_chr) {
		for (char *i = a_chr; *i; ++i) {
			*i = tolower(*i);
		}
	}

public:
	MediaDbReader() {
	}

	// Opens a file
	MediaDbReader(const char *a_filename) {
		open(a_filename);
	}

	// Opens a file, closes if one is already opened.
	// May throw invalid_argument if an error occured while opening the file.
	void open(const char *filename) throw (std::invalid_argument);

	// If a file currently opened.
	bool isOpened() {
		return m_reader.is_open();
	}

	// Rewinds the file/starts from the beginning!
	// Throws invalid_argument if an error occurs.
	void rewind() throw (std::invalid_argument) {
		m_reader.seekg(std::ios::beg);

		if (!m_reader.good()) {
			throw std::invalid_argument(
					"An error occured while rewinding file.");
		}
	}

	// Closes a file.
	// Throws invalid_argument if no file was opened.
	void close() throw (std::invalid_argument) {
		if (!m_reader.is_open()) {
			throw std::invalid_argument("No file was opened!");
		}

		m_reader.close();
	}

	// Reads next line that has data, returns NULL otherwise.
	// May throw invalid_argument if no file is opened,
	// if album name or release year could not be read, or if
	// an error occured during reading of the file.
	BaseMedia *readNext() throw (std::invalid_argument);
};

#endif /* MEDIADBREADER_H_ */
