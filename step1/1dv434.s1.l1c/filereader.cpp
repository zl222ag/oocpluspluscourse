#ifndef FILE_READER_CPP
#define FILE_READER_CPP

#include "filereader.h"

FileReader::~FileReader() {
	if (m_file.is_open()) {
		close();
	}
}

// Opens a file, if a file is already opened then it closes the previous one.
void FileReader::open(char *a_filename) {
	if (m_file.is_open()) {
		close();
	}
	m_file.open(a_filename);
	if (!m_file.is_open()) {
		throw runtime_error("Error on opening file!");
	}
}

// Is a file currently opened?
bool FileReader::isOpen() {
	return m_file.is_open();
}

// Closes the file, throws state_error if a file is not opened.
void FileReader::close() {
	if (!m_file.is_open()) {
		throw state_error("A file must be opened!");
	}
	m_file.close();
}

// Reads next Double, returns true if not EOF or non double value,
// throws state_error if a file is not opened.
bool FileReader::readNextDouble(double &a_var) {
	if (!m_file.is_open()) {
		throw state_error("A file must be opened!");
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
