#include <cstdlib>
#include <iostream>
#include "mediaregister.h"

using std::cout;
using std::endl;

class MediaApplication {
	MediaRegister m_register;

public:
	MediaApplication() {
	}

	int run();
};

int MediaApplication::run() {
	m_register.loadReg();
	m_register.saveReg("wabjers");
	m_register.showMedia();
	m_register.sortMedia();
	cout << endl << endl;
	m_register.showMedia();
	cout << endl << endl;
	cout << *m_register.findMedia("rush", "permanent waves");
	return EXIT_SUCCESS;
}

int main() {
	MediaApplication app;
	return app.run();
}
