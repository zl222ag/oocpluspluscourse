/*
 * Texthandler.h
 *
 *  Created on: 28 apr 2015
 *      Author: Zlatko Ladan
 */

#ifndef TEXTHANDLER_H_
#define TEXTHANDLER_H_

class Texthandler {
	static const int MAX_SIZE = 1000;

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
	}

	int antalTexter() {
		return m_size;
	}

	int maxAntalTexter() {
		return m_maxSize;
	}

	const char* text(int index);
};

#endif /* TEXTHANDLER_H_ */
