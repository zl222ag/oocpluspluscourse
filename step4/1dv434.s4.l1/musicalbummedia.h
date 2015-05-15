/*
 * musicalbummedia.h
 *
 *  Created on: 15 maj 2015
 *      Author: zlatko
 */

#ifndef MUSICALBUMMEDIA_H_
#define MUSICALBUMMEDIA_H_

#include "basemedia.h"

class MusicAlbumMedia: BaseMedia {
public:
	virtual ~MusicAlbumMedia() {

	}

	void show();

	int getId() {
		return 0;
	}
};

#endif /* MUSICALBUMMEDIA_H_ */
