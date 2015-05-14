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
#include <filereader.h>
#include "basemedia.h"

class MediaRegister {
	std::vector<BaseMedia> m_media;
	const char *m_dbFile;

public:
	MediaRegister(int a_startSize = 8, const char *a_dbFile = "media.dat") :
			m_media(a_startSize), m_dbFile(a_dbFile) {
		loadReg();
	}

	~MediaRegister() {
		emptyReg();
	}

	void addMedia(BaseMedia media);
	void removeMedia(const BaseMedia &media);
	BaseMedia *findMedia(){return NULL;} //FIXME FIX!
	void showMedia();
	void sortMedia();

	void emptyReg() {
		m_media.empty();
	}

	void saveReg();
	void loadReg();
};

#endif // MEDIAREGISTER_H_
