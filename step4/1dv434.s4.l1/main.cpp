#include <cstdlib>
#include <iostream>
#ifdef _DEBUG
#include <cstring>
#include<cassert>
#endif
#include <inputoutput.h>
#include <compare.h>
#include "mediaregister.h"

using std::cout;
using std::endl;

class MediaApplication {
	MediaRegister m_register;

public:
	MediaApplication() {
	}

#ifdef _DEBUG
	void test();
#endif

	int run();
};

int MediaApplication::run() {
#ifdef _DEBUG
	{
		char choice = '\0';

		do {
			cout << "Run test first?: ";
			InputOutput::readChar(choice);
			choice = tolower(choice);
			cout << endl;
		} while (choice != 'n' && choice != 'y');

		if (choice == 'y') {
			test();
		}
	}
#endif

	return EXIT_SUCCESS;
}

void MediaApplication::test() {
	m_register.loadReg();
	m_register.saveReg("wabjers");

	cout << "Check media: " << endl;
	m_register.showMedia();
	m_register.sortMedia();
	cout << endl << endl;

	cout << "Check sorted: " << endl;
	m_register.showMedia();
	cout << endl << endl;

	cout << "Is Rush's permanent waves on the \"shelf\"? (yes)" << endl;
	BaseMedia *media = m_register.findMedia("rUsh", "permanenT waVes");
	assert(media->getId() == MusicAlbumMedia::IDENTIFICATION);

	cout << "Is the album ok? (ought to be)" << endl;
	MusicAlbumMedia musicMedia = *(MusicAlbumMedia *) media;
	assert(Compare::equali(musicMedia.getArtistName(), "RUSH"));
	assert(Compare::equali(musicMedia.getAlbumName(), "Permanent Waves"));
	assert(musicMedia.getReleaseYear() == 1980);
	assert(musicMedia == MusicAlbumMedia("RuSH", "perManent WaVeS", 1980));

	BaseMedia *media2 = (BaseMedia *) new MusicAlbumMedia("rush",
		"permanent waves", 1980);
	assert(musicMedia == *media2);
	assert(*media == *media2);

	media2 = (BaseMedia *) new MusicAlbumMedia("oscar peterson",
		"soft sands", 1957);

	assert(!(*media == *media2));
	assert(*media != *media2);

	cout << "Is the album \"Back to back\" with Duke Ellington and "
			"Johnny Hodges on the \"shelf\"? (no)" << endl;
	media = m_register.findMedia("duke ellington & johnny hodges",
			"back to back");
	assert(media == NULL);
}

int main() {
	MediaApplication app;
	return app.run();
}
