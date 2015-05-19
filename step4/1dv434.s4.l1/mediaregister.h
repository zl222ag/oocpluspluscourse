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

	static void show(BaseMedia *a_media) {
		cout << *a_media << endl;
	}

	// is there a better way? (Not a rhetorical question)
	static bool sorter(BaseMedia *a_amedia, BaseMedia *a_bmedia) {
		return *a_amedia < *a_bmedia;
	}

public:
	MediaRegister() {
	}

	~MediaRegister() {
		emptyReg();
	}

	void addMedia(BaseMedia *a_media) {
		m_media.push_back(a_media);
	}

	void removeMedia(const BaseMedia *a_media) {
		std::remove(m_media.begin(), m_media.end(), a_media);
	}

	BaseMedia *findMedia(const char *a_artistName, const char *a_albumName) {
		//std::find(m_media.begin(), m_media.end(), )
		
		return *std::find_if(m_media.begin(), m_media.end(), [&](BaseMedia *a_media) {
			if (a_media->getId() != MusicAlbumMedia::IDENTIFICATION) {
				return false;
			}

			MusicAlbumMedia *data = (MusicAlbumMedia *) a_media;
			return strcmp(a_artistName, data->getArtistName()) == 0 &&
				strcmp(a_albumName, data->getAlbumName()) == 0;
		});
	}

	void showMedia() {
		std::for_each(m_media.begin(), m_media.end(), show);
	}

	void sortMedia() {
		// Is there a better way? (Not a rhetorical question)
		std::sort(m_media.begin(), m_media.end(), sorter);
	}

	void emptyReg() {
		m_media.empty();
	}

	void saveReg(const char *a_dbFile = "media.dat");
	void loadReg(const char *a_dbFile = "media.dat");
};

#endif // MEDIAREGISTER_H_
