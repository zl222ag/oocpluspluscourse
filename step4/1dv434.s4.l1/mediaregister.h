/*
 * mediaregister.h
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef MEDIAREGISTER_H_
#define MEDIAREGISTER_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <filereader.h>
#include "basemedia.h"
#include "musicalbummedia.h"
#include <iostream>

using std::cout;
using std::endl;

class MediaRegister {
	std::vector<BaseMedia *> m_media;

	// Is used together with showMedia's for_each!
	static void show(BaseMedia *a_media) {
		cout << *a_media << endl;
	}

	// is there a better way? (Not a rhetorical question)
	static bool sorter(BaseMedia *a_amedia, BaseMedia *a_bmedia) {
		return *a_amedia < *a_bmedia;
	}

	static void empty(BaseMedia *a_media) {
		delete a_media;
	}

public:
	MediaRegister() {
	}

	~MediaRegister() {
		emptyReg(); // NOT REALLY NECESSARY
	}

	// Adds media (creates copy)!
	void addMedia(BaseMedia *a_media) {
		m_media.push_back(a_media);
	}

	// Removes a media!
	void removeMedia(const BaseMedia *a_media) {
		std::remove(m_media.begin(), m_media.end(), a_media);
	}

	BaseMedia *findMedia(const char *artistName, const char *albumName);

	void showMedia() {
		std::for_each(m_media.begin(), m_media.end(), show);
	}

	void sortMedia() {
		// Is there a better way? (Not a rhetorical question)
		std::sort(m_media.begin(), m_media.end(), sorter);
	}

	void emptyReg() {
		std::for_each(m_media.begin(), m_media.end(), empty);
		m_media.empty();
	}

	void saveReg(const char *a_dbFile = "media.dat");
	void loadReg(const char *a_dbFile = "media.dat");
};

#endif // MEDIAREGISTER_H_
