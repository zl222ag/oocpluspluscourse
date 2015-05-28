#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <stdexcept>

// To be used with erroneous states.
// For instance when closing a file that is not even opened.
class state_error : public std::logic_error {
public:
	state_error(const char *a_msg) :
			std::logic_error(a_msg) {
	}
};

class FileReader {
private:
	std::ifstream m_file;

public:
	~FileReader() {
		if (m_file.is_open()) {
			close();
		}
	}

	// Opens a file, if a file is already opened then it closes the previous one.
	// May throw runtime error if an error occurs while opening file.
	void open(char *) throw (std::runtime_error);

	// Is a file currently opened?
	bool isOpen() const {
		return m_file.is_open();
	}

	// Closes the file, throws state_error if a file is not opened.
	void close() {
		if (!m_file.is_open()) {
			throw state_error("A file must be opened!");
		}

		m_file.close();
	}

	// Reads next Double, returns true if not EOF or non double value,
	// throws state_error if a file is not opened.
	bool readNextDouble(double &) throw(state_error);
};

#endif // FILE_READER_H
