/*
 * Texthandler.h
 *
 *  Created on: 28 apr 2015
 *      Author: Zlatko Ladan
 */

#if defined(_WIN32) || defined(_WIN64)
#define _WINDOWS
#endif

#ifndef TEXTHANDLER_H_
#define TEXTHANDLER_H_

#include <cstring>
#include <stdexcept>

class Texthandler {
#ifdef _WINDOWS
	typedef rsize_t zsize_t;
#else
	typedef size_t zsize_t;
#endif

	static const zsize_t MAX_TOTAL_SIZE = 10000;
	static const zsize_t MAX_LINE_SIZE = 256;
	static const char *DELIMITER /* "%%%%%" */;

	const int MAX_SIZE;
	char **m_texts;
	int m_size;

	// Reads the file.
	void laesFil(const char *filename) throw (std::invalid_argument,
			std::length_error);

public:
	// a_fileName: the filename!
	// a_maxSize: the size limitation for texts.
	Texthandler(const char *a_fileName, const int a_maxSize)
			throw (std::invalid_argument, std::length_error) :
			MAX_SIZE(a_maxSize), m_texts(new char*[a_maxSize]), m_size(0) {

		for (int i = 0; i < a_maxSize; ++i) {
			m_texts[i] = NULL;
		}

		laesFil(a_fileName);
	}

	~Texthandler() {
		if (m_texts != NULL) {
			for (int i = 0; i < m_size; ++i) {
				delete[] m_texts[i];
			}

			delete[] m_texts;
		}
	}

	// Returns the amount of texts.
	int antalTexter() const {
		return m_size;
	}

	// Returns the limit of the amount of texts.
	int maxAntalTexter() const {
		return MAX_SIZE;
	}

	// Safe string copying.
	static void stringCopy(char *a_dest, const char *a_src, zsize_t a_size) {
#ifdef _WINDOWS
		strcpy_s(a_dest, a_size, a_src);
#else
		strncpy(a_dest, a_src, a_size);
#endif
	}

	// Safe string concatenation.
	static void stringConcatenate(char *a_dest, const char *a_src,
			zsize_t a_size) {
#ifdef _WINDOWS
		strcat_s(a_dest, a_size, a_src);
#else
		strncat(a_dest, a_src, a_size);
#endif
	}

	// Not index, a_pos starts at 1, NOT 0!
	// if a_pos is not within the right range, then NULL is returned.
	const char* text(int a_pos) const {
		if (a_pos < 1 || a_pos > m_size) {
			return NULL;
		}

		return m_texts[a_pos - 1];
	}
};

#endif // TEXTHANDLER_H_
