/*
 * tester.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: zlatko
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include "tester.h"
#include "mediaregister.h"
#include "mediadbreader.h"

using std::cout;
using std::endl;
using std::invalid_argument;

// Runs the tests for the media register class.
void Tester::testRegister() {
	MediaRegister m_register;
	const char tmpJunkFile[] = "wabjers.tmp";
	m_register.loadReg();

	cout << "Check media: " << endl;
	m_register.showMedia();
	cout << endl;

	m_register.sortMedia();
	cout << "Check sorted: " << endl;
	m_register.showMedia();
	cout << endl;

	cout << "Trying to save to file \"" << tmpJunkFile << "\" (should work)!"
			<< endl;
	m_register.saveReg(tmpJunkFile);
	std::ifstream file(tmpJunkFile);
	assert(file.good());
	file.close();
	cout << endl;

	cout << "Emptying register, should be empty" << endl << "--start--" << endl;
	m_register.emptyReg();
	m_register.showMedia();
	cout << "--end--" << endl << endl;

	cout << "Testing newly saved wabjers!" << endl << endl;
	MediaDbReader reader(tmpJunkFile);
	BaseMedia *media = NULL;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("dire straits", "brothers in arms", 1985));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("earth wind and fire",
							"that's the way of the world", 1975));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("fleetwood mac", "rumours", 1977));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("JUDAS PRIEST", "KILLING machine", 1978));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("oscar peterson", "soft sands", 1957));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("pink floyd", "wish you where here",
							1975));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "hemispheres", 1978));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "moving pictures", 1981));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "permanent waves", 1980));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("sting", "...nothing like the sun", 1987));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("the police", "ghost in the machine",
							1981));
	delete media;

	media = reader.readNext();
	assert(media == NULL);

	std::remove(tmpJunkFile);
}

// Runs tests for the music album media class.
void Tester::testMusicAlbumMedia() {
	bool thrown;
	MediaRegister m_register;
	m_register.loadReg();

	cout << "Is Rush's permanent waves on the \"shelf\"? (yes)" << endl;
	BaseMedia *media = m_register.findMedia("rUsh", "permanenT waVes");
	assert(media != NULL);
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
	assert(*media2 == musicMedia);
	assert(*media == *media2);
	assert(*media2 == *media);

	delete media2;

	cout << "Checking difference between Rush's Permanent Waves and"
			"Oscar Peterson's Soft Sands!" << endl;

	media2 = (BaseMedia *) m_register.findMedia("oscar peterson", "soft sands");
	assert(media2 != NULL);

	assert(!(*media == *media2));
	assert(!(*media2 == *media));
	assert(*media != *media2);
	assert(*media2 != *media);

	cout << endl << "Is the album \"Back to back\" with Duke Ellington and "
			"Johnny Hodges on the \"shelf\"? (no)" << endl;
	media = m_register.findMedia("duke ellington & johnny hodges",
			"back to back");
	assert(media == NULL);

	cout << endl << "Does no album equal no album?" << endl;
	assert(MusicAlbumMedia() == MusicAlbumMedia());
	assert(!(MusicAlbumMedia() != MusicAlbumMedia()));

	cout << endl << "Testing to set a field to NULL (should cause exception)"
			<< endl;

	try {
		thrown = false;
		MusicAlbumMedia(NULL, NULL, 0);
	} catch (const std::invalid_argument &e) {
		thrown = true;
	}

	assert(thrown);

	try {
		thrown = false;
		MusicAlbumMedia("testing", NULL, 0);
	} catch (const std::invalid_argument &e) {
		thrown = true;
	}

	assert(thrown);

	try {
		thrown = false;
		MusicAlbumMedia(NULL, "testing", 0);
	} catch (const std::invalid_argument &e) {
		thrown = true;
	}

	assert(thrown);

	cout << endl;
}

// Runs the tests for the media reader class!
void Tester::testMediaReader() {
	MediaDbReader reader;
	int i = 0;
	bool thrown;
	BaseMedia *media = NULL;

	cout << "Checking if reading nothing causes an invalid_argument exception"
			<< endl;

	try {
		thrown = false;
		reader.readNext();
	} catch (const std::invalid_argument &e) {
		thrown = true;
	}

	assert(thrown);

	cout << endl
			<< "Comparing all values from media.dat (case, ends with NULL)."
			<< endl;
	reader.open("media.dat");

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("dire straits", "brothers in arms", 1985));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("earth wind and fire",
							"that's the way of the world", 1975));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("pink floyd", "wish you where here",
							1975));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("sting", "...nothing like the sun", 1987));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "hemispheres", 1978));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "permanent waves", 1980));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("rush", "moving pictures", 1981));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("oscar peterson", "soft sands", 1957));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("the police", "ghost in the machine",
							1981));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("fleetwood mac", "rumours", 1977));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("judas priest", "killing machine", 1978));
	assert(
			Compare::equal(((MusicAlbumMedia * ) media)->getArtistName(),
					"judas priest"));
	assert(
			Compare::equal(((MusicAlbumMedia * ) media)->getAlbumName(),
					"killing machine"));
	assert((((MusicAlbumMedia * ) media)->getReleaseYear()) == 1978);
	delete media;

	media = reader.readNext();
	assert(media == NULL);

	reader.open("broken1.dat");

	cout << endl << "Testing broken1.dat (broken file), which should cause an"
			"exception at line 4!" << endl;
	try {
		thrown = false;

		while ((media = reader.readNext()) != NULL) {
			++i;
			delete media;
		}
	} catch (const std::invalid_argument &e) {
		assert(i == 4);
		thrown = true;
	}

	assert(thrown);

	cout << endl << "Testing broken2.dat (broken file), which should cause an"
			"exception at line 3!" << endl;

	reader.open("broken2.dat");

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("dire straits", "money for nothing",
							1988));
	delete media;

	media = reader.readNext();
	assert(*media == MusicAlbumMedia("earth wind and fire", "raise!", 1981));
	delete media;

	media = reader.readNext();
	assert(
			*media
					== MusicAlbumMedia("pink floyd", "dark side of the moon",
							1973));
	assert(*media != MusicAlbumMedia("pink floyd", "animals", 1977));
	assert(MusicAlbumMedia("pink floyd", "animals", 1977) != *media);
	assert(MusicAlbumMedia() != *media);
	assert(*media != MusicAlbumMedia());
	assert(
			!(MusicAlbumMedia("pink floyd", "dark side of the moon", 1973)
					!= *media));
	assert(
			!(*media
					!= MusicAlbumMedia("pink floyd", "dark side of the moon",
							1973)));
	assert(
			!(MusicAlbumMedia("pink floyd", "dark side of the moon", 1973)
					!= *media));

	delete media;

	try {
		thrown = false;
		media = reader.readNext();
	} catch (const std::invalid_argument &e) {
		thrown = true;
	}

	assert(thrown);
	cout << endl;
}

// Runs all the tests!
void Tester::runTests() {
	testRegister();
	testMusicAlbumMedia();
	testMediaReader();
}
