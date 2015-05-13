#include <cstdlib>
#include "mediaregister.h"

class MediaApplication {
	MediaRegister m_register;

public:
	MediaApplication() : m_register(100) {
	}

	int run();
};

int MediaApplication::run() {
	return EXIT_SUCCESS;
}

int main() {
	MediaApplication app;
	return app.run();
}
