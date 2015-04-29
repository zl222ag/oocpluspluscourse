/*
 * Texthandler.h
 *
 *  Created on: 28 apr 2015
 *      Author: Zlatko Ladan
 */

#ifndef TEXTHANDLER_H_
#define TEXTHANDLER_H_

#include <cstring>

class Texthandler {
	static const int MAX_SIZE = 10000;
	static const char *DELIMITER /* "%%%%%" */;

	char **m_texts;
	const int m_maxSize;
	int m_size;

	void laesFil(const char *filename);

public:
	Texthandler(const char *a_fileName, const int a_maxSize) :
			m_maxSize(a_maxSize) {
		m_texts = new char*[a_maxSize];
		m_size = 0;
		laesFil(a_fileName);

		for (int i = 0; i < a_maxSize; ++i) {
			m_texts[i] = NULL;
		}
	}

	int antalTexter() {
		return m_size;
	}

	int maxAntalTexter() {
		return m_maxSize;
	}

	void stringCopy(char *a_dest, const char *a_src, size_t a_size) {
#if defined(_WIN32) || defined(_WIN64)
		strcpy_s(a_dest, a_size, a_src);
#endif
		strncpy(a_dest, a_src, a_size);
	}

	void stringConcatinate(char *a_dest, const char *a_src, size_t a_size) {
#if defined(_WIN32) || defined(_WIN64)
		strcat_s(a_dest, a_size, a_src);
#endif
		strncat(a_dest, a_src, a_size);
	}

	const char* text(int pos);
};

#endif /* TEXTHANDLER_H_ */
