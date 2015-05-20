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

class BaseMedia;

class MediaDbWriter {
		static const char DELIMITER = '|';
		static const int ARTIST_NAME_MAX_LENGTH = 128,
			ALBUM_NAME_MAX_LENGTH = 128,
			YEAR_CHAR_MAX_LENGTH = 10;
		std::ofstream m_writer;

	public:
		MediaDbWriter(const char *a_filename) {
			open(a_filename);
		}

		void open(const char *filename);

		void close() {
			m_writer.close();
		}

		// Returns a media (must be deleted),
		void writeNext(const BaseMedia *) throw(std::invalid_argument);
	};

#endif // MEDIADBWRITER_H_

