/*
 * mediadbreader.h
 *
 *  Created on: 14 maj 2015
 *      Author: zlatko
 */

#ifndef MEDIADBREADER_H_
#define MEDIADBREADER_H_

#include <fstream>

class BaseMedia;

class MediaDbReader {
	static const char DELIMITER = '|';
	std::ifstream m_reader;

public:
	MediaDbReader(const char *a_filename) {
		open(a_filename);
	}

	void open(const char *filename);

	void close() {
		m_reader.close();
	}

	BaseMedia *read();
};

#endif /* MEDIADBREADER_H_ */
