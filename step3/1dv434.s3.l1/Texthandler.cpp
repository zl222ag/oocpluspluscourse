/*
 * Texthandler.cpp
 *
 *  Created on: 28 apr 2015
 *      Author: Zlatko Ladan
 */

#include <fstream>
#include <cstring>
#include <iostream>
#include "Texthandler.h"

using std::fstream;

const char *Texthandler::DELIMITER = "%%%%%";

//TODO: add comment
void Texthandler::laesFil(const char *a_fileName) {
	fstream stream(a_fileName);
	char temp[MAX_LINE_SIZE];
	bool foundDelimiter, last = false;
	int i = 0;

#if defined(WIN32) || defined(_WIN64)
	char *p; // åäö fix for display! (charset win-1252)
#endif

	if (!stream || stream.eof()) {
		return;
	}

	stream.getline(temp, MAX_LINE_SIZE);

	if (strcmp(temp, DELIMITER) != 0) {
		std::cerr << "Fel: borde börja med " << DELIMITER << '!' << std::endl;
		return;
	}

	while (!stream.eof() && i < m_maxSize && !last) {
		foundDelimiter = false;

		while (!stream.eof() && !foundDelimiter && !last) {
			stream.getline(temp, MAX_LINE_SIZE);
			foundDelimiter = strcmp(temp, DELIMITER) == 0;

			if (stream.gcount() < 1) {
				if (m_texts[i] == NULL) {
					last = true;
				} else {
					// ERROR!!
					return;
				}
			} else if (!foundDelimiter) {
				temp[stream.gcount() - 1] = '\n';
				temp[stream.gcount()] = '\0';

				if (m_texts[i] == NULL) {
					m_texts[i] = new char[MAX_TOTAL_SIZE];
					stringCopy(m_texts[i], temp, MAX_TOTAL_SIZE);
				} else {
					if (strlen(m_texts[i]) + strlen(temp) >= MAX_TOTAL_SIZE) {
						std::cerr << "Fel: Texten tar mer än "
							<< MAX_TOTAL_SIZE << " tecken." << std::endl;
						m_size = i + 1;
						return;
					}
					stringConcatinate(m_texts[i], temp, MAX_TOTAL_SIZE);
				}
			}
		}

		if (!last) {
#if defined(WIN32) || defined(_WIN64)
			p = m_texts[i];

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
#endif
			++i;
		}
	}

	m_size = i;
}
