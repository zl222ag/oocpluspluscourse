/*
 * tester.cpp
 *
 *  Created on: 22 maj 2015
 *      Author: zlatko
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "tester.h"
#include "mediaregister.h"
#include "mediadbreader.h"

using std::cout;
using std::endl;
using std::vector;
using std::invalid_argument;

// Runs the tests for the media register class.
void Tester::testRegister() {
	MediaRegister mediaRegister;
	const char tmpJunkFile[] = "wabjers.tmp";
	bool thrown;
	mediaRegister.loadReg();

	cout << "Check media: " << endl;
	mediaRegister.showMedia();

	mediaRegister.sortMedia();
	cout << endl << "Check sorted: " << endl;
	mediaRegister.showMedia();

	cout << endl << "Trying to save to file \"" << tmpJunkFile
			<< "\" (should work)!" << endl;
	mediaRegister.saveReg(tmpJunkFile);
	std::ifstream file(tmpJunkFile);
	assert(file.good());
	file.close();

	cout << endl << "Emptying register, should be empty" << endl << "--start--"
			<< endl;
	mediaRegister.emptyReg();
	mediaRegister.showMedia();
	cout << "--end--" << endl;

	cout << endl << "Testing newly saved wabjers!" << endl;
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

	cout << endl << "Rushing to find rush (should be 3 elements)." << endl;
	mediaRegister.loadReg();

	vector<BaseMedia *> mediaVec = mediaRegister.findMedia("rush");
	assert(mediaVec.size() == 3);
	assert(*mediaVec[0] == MusicAlbumMedia("Rush", "Hemispheres", 1978));
	assert(*mediaVec[1] == MusicAlbumMedia("Rush", "Permanent waves", 1980));
	assert(*mediaVec[2] == MusicAlbumMedia("Rush", "Moving Pictures", 1981));
	delete mediaVec[0];
	delete mediaVec[1];
	delete mediaVec[2];

	cout << endl << "Checking for Judas Priest (should be 1 element)." << endl;

	mediaVec = mediaRegister.findMedia("JUDAS priest");
	assert(mediaVec.size() == 1);
	assert(
			*mediaVec[0]
					== MusicAlbumMedia("Judas Priest", "killing machine",
							1978));
	delete mediaVec[0];

	cout << endl << "Trying to add Judas Priest - Killing Machine "
			"(should throw invalid_argument)." << endl;

	try {
		thrown = false;
		mediaRegister.addMedia(
				MusicAlbumMedia("Judas Priest", "killing machine", 1978));
	} catch (const invalid_argument &) {
		thrown = true;
	}

	assert(thrown);

	cout << endl << "Replacing Judas priest's killing machine, with "
			"learning machine." << endl;
	mediaRegister.replaceMedia(
			MusicAlbumMedia("Judas Priest", "killing machine", 1978),
			MusicAlbumMedia("Judas Priest", "learning machine", 1978));
	assert(
			(media = mediaRegister.findMedia("judas priest", "learning machine")) != NULL);
	delete media;

	cout << "Replacing Rush's Hemispheres with Stratospheres." << endl;

	mediaRegister.replaceMedia(MusicAlbumMedia("rush", "hemispheres", 1978),
			 MusicAlbumMedia("RUSH", "stratospheres", 1976));
	assert((media = mediaRegister.findMedia("RuSH", "StratosPHeres")) != NULL);
	delete media;

	cout << "Removing Rush's Stratospheres." << endl;
	assert(
			mediaRegister.removeMedia(
					MusicAlbumMedia("RUSH", "stratospheres", 1976)));
	assert((media = mediaRegister.findMedia("RuSH", "StratosPHeres")) == NULL);
	delete media;

	cout << "Searching and checking for Sting's ...Nothing Like The Sun." << endl;
	assert((media = mediaRegister.findMedia("Sting", "...nothing LIKE THE SUN")) != NULL);
	assert(*media == MusicAlbumMedia("sting", "...nothing like the sun", 1987));
	delete media;

	cout << "Searching and removing Rush's Moving Pictures." << endl;
	assert((media = mediaRegister.findMedia("Rush", "Moving pictures")) != NULL);
	assert(mediaRegister.removeMedia(*media));
	delete media;
	assert((media = mediaRegister.findMedia("Rush", "Moving pictures")) == NULL);
}

// Runs tests for the music album media class.
void Tester::testMusicAlbumMedia() {
	bool thrown;
	MediaRegister mediaRegister;
	mediaRegister.loadReg();

	cout << endl << "Is Rush's permanent waves on the \"shelf\"? (yes)" << endl;
	BaseMedia *media = mediaRegister.findMedia("rUsh", "permanenT waVes");
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

	cout << "Checking difference between Rush's Permanent Waves and "
			"Oscar Peterson's Soft Sands!" << endl;

	media2 = (BaseMedia *) mediaRegister.findMedia("oscar peterson",
			"soft sands");
	assert(media2 != NULL);

	assert(!(*media == *media2));
	assert(!(*media2 == *media));
	assert(*media != *media2);
	assert(*media2 != *media);

	delete media2;

	cout << endl << "Is the album \"Back to back\" with Duke Ellington and "
			"Johnny Hodges on the \"shelf\"? (no)" << endl;
	delete media;
	media = mediaRegister.findMedia("duke ellington & johnny hodges",
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
	} catch (const std::invalid_argument &) {
		thrown = true;
	}

	assert(thrown);

	try {
		thrown = false;
		MusicAlbumMedia("testing", NULL, 0);
	} catch (const std::invalid_argument &) {
		thrown = true;
	}

	assert(thrown);

	try {
		thrown = false;
		MusicAlbumMedia(NULL, "testing", 0);
	} catch (const std::invalid_argument &) {
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
	} catch (const std::invalid_argument &) {
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
	} catch (const std::invalid_argument &) {
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
	} catch (const std::invalid_argument &) {
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
