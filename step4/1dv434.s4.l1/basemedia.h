/*
 * basemedia.h
 *
 *  Created on: 12 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef BASEMEDIA_H_
#define BASEMEDIA_H_

#include <iostream>

class BaseMedia {
	virtual std::ostream &print(std::ostream &) const = 0;

public:
	friend std::ostream &operator<<(std::ostream &a_ostream,
			const BaseMedia &a_media) {
		return a_media.print(a_ostream);
	}

	virtual ~BaseMedia() {
	}
	virtual int getId() const = 0;
	virtual bool operator==(const BaseMedia &) const = 0;
	virtual bool operator<(const BaseMedia &) const = 0;
};

#endif // BASEMEDIA_H_
