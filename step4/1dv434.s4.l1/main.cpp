#include <cstdlib>

class MediaApplication {
public:
	int run();
};

int MediaApplication::run() {
	return EXIT_SUCCESS;
}

int main() {
	MediaApplication app;
	return app.run();
}
