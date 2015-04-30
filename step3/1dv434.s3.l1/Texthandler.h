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
#if defined(_WIN32) || defined(_WIN64)
	typedef rsize_t zsize_t;
#else
	typedef size_t zsize_t;
#endif

	static const size_t MAX_TOTAL_SIZE = 10000;
	static const size_t MAX_LINE_SIZE = 256;
	static const char *DELIMITER /* "%%%%%" */;

	char **m_texts = NULL;
	const int m_maxSize;
	int m_size;

	//TODO: add comment
	void laesFil(const char *filename);

public:
	//TODO: add comment
	Texthandler(const char *a_fileName, const int a_maxSize) :
		m_maxSize(a_maxSize) {
		m_texts = new char*[a_maxSize];
		m_size = 0;

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

	//TODO: add comment
	int antalTexter() {
		return m_size;
	}

	//TODO: add comment
	int maxAntalTexter() {
		return m_maxSize;
	}

	//TODO: add comment
	void stringCopy(char *a_dest, const char *a_src, zsize_t a_size) {
#if defined(_WIN32) || defined(_WIN64)
		strcpy_s(a_dest, a_size, a_src);
#else
		strncpy(a_dest, a_src, a_size);
#endif
	}

	//TODO: add comment
	void stringConcatinate(char *a_dest, const char *a_src, zsize_t a_size) {
#if defined(_WIN32) || defined(_WIN64)
		strcat_s(a_dest, a_size, a_src);
#else
		strncat(a_dest, a_src, a_size);
#endif
	}

	// Not index, a_pos starts at 1, NOT 0!
	const char* text(int a_pos) {
		if (a_pos < 1 || a_pos > m_size) {
			return NULL;
		}

		return m_texts[a_pos - 1];
	}
};

#endif /* TEXTHANDLER_H_ */
