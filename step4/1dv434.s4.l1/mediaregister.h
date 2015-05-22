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

class MediaRegister {
	std::vector<BaseMedia *> m_media;

	// Is used together with showMedia's for_each!
	static void show(BaseMedia *a_media) {
		std::cout << *a_media << std::endl;
	}

	// Is there a better way? (Not a rhetorical question)
	// Compares media
	static bool sorter(BaseMedia *a_aMedia, BaseMedia *a_bMedia) {
		return *a_aMedia < *a_bMedia;
	}

	// Deletes a media from register (to be used with for loop).
	static void empty(BaseMedia *a_media) {
		delete a_media;
	}

public:
	MediaRegister() {
	}

	~MediaRegister() {
		emptyReg();
	}

	// Adds media (creates copy)!
	void addMedia(BaseMedia *a_media) {
		m_media.push_back(a_media);
	}

	// Removes a media!
	void removeMedia(const BaseMedia *a_media) {
		std::remove(m_media.begin(), m_media.end(), a_media);
	}

	// Finds the specified media.
	BaseMedia *findMedia(const char *artistName, const char *albumName);

	// Shows data for media.
	void showMedia() {
		std::for_each(m_media.begin(), m_media.end(), show);
	}

	// Sorts media.
	void sortMedia() {
		// Is there a better way? (Not a rhetorical question)
		std::sort(m_media.begin(), m_media.end(), sorter);
	}

	// Removes all data from register.
	void emptyReg() {
		std::for_each(m_media.begin(), m_media.end(), empty);
		m_media.clear();
	}

	// Saves register to file.
	void saveReg(const char *a_dbFile = "media.dat")
			throw (std::invalid_argument);
	// Loads register from file.
	void loadReg(const char *a_dbFile = "media.dat")
			throw (std::invalid_argument);
};

#endif // MEDIAREGISTER_H_
