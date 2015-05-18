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

class MediaRegister {
	std::vector<BaseMedia *> m_media;
	const char *m_dbFile;

	static void show(BaseMedia *a_media) {
		a_media->show();
	}

public:
	MediaRegister(int a_startSize = 8, const char *a_dbFile = "media.dat") :
			m_media(std::vector<BaseMedia *>(a_startSize)), m_dbFile(a_dbFile) {
		loadReg();
	}

	~MediaRegister() {
		emptyReg();
	}

	void addMedia(BaseMedia *a_media) {
		m_media.push_back(a_media);
	}

	void removeMedia(const BaseMedia &a_media) {
		std::remove(m_media.begin(), m_media.end(), a_media);
	}

	BaseMedia *findMedia() {
		return NULL; // FIXME FIX!
	}

	void showMedia() {
		std::for_each(m_media.begin(), m_media.end(), MediaRegister::show);
	}

	void sortMedia() {
		std::sort(m_media.begin(), m_media.end());
	}

	void emptyReg() {
		m_media.empty();
	}

	void saveReg();
	void loadReg();
};

#endif // MEDIAREGISTER_H_
