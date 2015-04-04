#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <stdexcept>

using std::ifstream;
using std::logic_error;

class state_error : public logic_error {
public:
	state_error(const char *a_msg) : logic_error(a_msg) {}
};

class FileReader {
private:
	ifstream m_file;

public:
	void open(char *);
	bool isOpen();
	void close();
	bool readNextDouble(double &);
};

#endif // FILE_READER_H
