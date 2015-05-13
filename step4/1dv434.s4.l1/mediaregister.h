/*
 * mediaregister.h
 *
 *  Created on: 13 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef MEDIAREGISTER_H_
#define MEDIAREGISTER_H_

#include <vector>
#include "basemedia.h"
#include <iostream>

class MediaRegister {
	std::vector<BaseMedia> m_media;

public:
	MediaRegister(int a_startSize = 8) : m_media(a_startSize) {
		std::cout << m_media.size() << std::endl;
	}
};

#endif // MEDIAREGISTER_H_
