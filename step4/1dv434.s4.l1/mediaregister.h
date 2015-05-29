/*
 * mediaregister.h
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef MEDIAREGISTER_H_
#define MEDIAREGISTER_H_

#include <list>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <filereader.h>
#include "basemedia.h"
#include "musicalbummedia.h"

class MediaRegister {
	std::list<BaseMedia *> m_media;

	// Is used together with showMedia's for_each!
	static void show(BaseMedia *a_media) {
		std::cout << *a_media << std::endl;
	}

	// Is there a better way? (Not a rhetorical question)
	// Compares media, whats lower.
	static bool sorter(BaseMedia *a_aMedia, BaseMedia *a_bMedia) {
		return *a_aMedia < *a_bMedia;
	}

	// Deletes a media from register (to be used with for loop).
	static void empty(BaseMedia *a_media) {
		std::cout << *a_media << std::endl;
		delete a_media;
	}

public:
	MediaRegister() {
	}

	~MediaRegister() {
		emptyReg();
	}

	// Adds media!
	// May throw invalid_argument if a_media is NULL or if the element
	// has already been added.
	void addMedia(const BaseMedia &media) throw (std::invalid_argument);

	// Removes a media!
	bool removeMedia(const BaseMedia &);

	// Finds the specified media by artist name and album name.
	// May return NULL if the specified media was not found.
	BaseMedia *findMedia(const char *artistName, const char *albumName) const;

	// Finds the specified media's by artist's name.
	std::list<BaseMedia *> findMedia(const char *artistName) const;

	// Shows data for media.
	void showMedia() const {
		std::for_each(m_media.begin(), m_media.end(), show);
	}

	// Sorts media.
	void sortMedia() {
		// Is there a better way? (Not a rhetorical question)
		m_media.sort(sorter);
	}

	// Replaces media
	// May throw invalid_argument if a_media has already been added.
	bool replaceMedia(const BaseMedia &from, const BaseMedia &to);

	// Removes all data from register.
	void emptyReg() {
		std::for_each(m_media.begin(), m_media.end(), empty);
		m_media.clear();
	}

	// Is the register empty.
	bool isEmptyReg() const {
		return m_media.empty();
	}

	// Saves register to file.
	// May throw invalid_argument if a_dbFile is NULL.
	void saveReg(const char *a_dbFile = "media.dat") const
			throw (std::invalid_argument);
	// Loads register from file.
	// May throw invalid_argument if a_dbFile is NULL or
	// if an error occurs during the reading of the file.
	void loadReg(const char *a_dbFile = "media.dat")
			throw (std::invalid_argument);
};

#endif // MEDIAREGISTER_H_
