#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <stdexcept>

using std::ifstream;
using std::logic_error;
using std::runtime_error;

// To be used with erroneous states.
// For instance when closing a file that is not even opened.
class state_error : public logic_error {
public:
	state_error(const char *a_msg) : logic_error(a_msg) {}
};

class FileReader {
private:
	ifstream m_file;

public:
    ~FileReader();

    // Opens a file, if a file is already opened
    // then it closes the previous one.
	void open(char *);

	// Is a file currently opened?
	bool isOpen();

	// Closes the file, throws state_error if a file is not opened.
	void close();

	// Reads next Double, returns true if not EOF or non double value,
	// throws state_error if a file is not opened.
	bool readNextDouble(double &);
};

#endif // FILE_READER_H
