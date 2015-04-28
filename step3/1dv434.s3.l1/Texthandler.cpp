/*
 * Texthandler.cpp
 *
 *  Created on: 28 apr 2015
 *      Author: Zlatko Ladan
 */

#include "Texthandler.h"
#include <fstream>

using std::fstream;

void Texthandler::laesFil(const char *a_fileName) {
	fstream stream(a_fileName);
	char *p;
	char *temp = new char[MAX_SIZE];

	if (!stream) {
		return;
	}

	while (!stream.eof() && m_size < m_maxSize) {
		stream.getline(temp, MAX_SIZE);
		p = temp;

		while (*p) {
			// håller på tills den träffar '\0'

			switch (*p) {
			case -59:
				*p = -113;
				break;

			case -60:
				*p = -114;
				break;

			case -42:
				*p = -103;
				break;

			case -27:
				*p = -122;
				break;

			case -28:
				*p = -124;
				break;

			case -10:
				*p = -108;
				break;
			}

			++p;
		}

		m_texts[m_size] = temp;
		++m_size;
	}
}

const char* Texthandler::text(int a_index) {
	return m_texts[a_index];
}
