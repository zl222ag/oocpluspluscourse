#ifndef FILE_READER_CPP
#define FILE_READER_CPP

#include "filereader.h"

void FileReader::open(char *a_filename) {
	if (m_file.is_open()) {
		close();
	}
	m_file.open(a_filename);
	if (!m_file.is_open()) {
		throw new std::runtime_error("Error on opening file!");
	}
}

bool FileReader::isOpen() {
	return m_file.is_open();
}

void FileReader::close() {
	if (!m_file.is_open()) {
		throw new state_error("A file must be opened!");
	}
	m_file.close();
}

bool FileReader::readNextDouble(double &a_var) {
	if (!m_file.is_open()) {
		throw new state_error("A file must be opened!");
	}
	double tmp = 0.0;
	m_file >> tmp;
	if (m_file.eof() || m_file.fail()) {
		return false;
	}
	a_var = tmp;
	return true;
}

#endif // FILE_READER_CPP
