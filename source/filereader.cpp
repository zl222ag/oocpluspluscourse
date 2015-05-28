#include <filereader.h>

using std::runtime_error;

// Opens a file, if a file is already opened then it closes the previous one.
// May throw runtime error if an error occurs while opening file.
void FileReader::open(char *a_filename) throw (runtime_error) {
	if (m_file.is_open()) {
		close();
	}

	m_file.open(a_filename);

	if (!m_file.is_open()) {
		throw runtime_error("Error on opening file!");
	}
}

// Reads next Double, returns true if not EOF or non double value,
// throws state_error if a file is not opened.
bool FileReader::readNextDouble(double &a_var) throw (state_error) {
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
