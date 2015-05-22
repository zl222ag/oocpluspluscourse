/*
 * basemedia.h
 *
 *  Created on: 12 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef BASEMEDIA_H_
#define BASEMEDIA_H_

#include <ostream>

class BaseMedia {
	// For output with cout or a file. Is used by friend std::operator.
	virtual std::ostream &print(std::ostream &) const = 0;

public:
	// For output with cout or a file.
	friend std::ostream &operator<<(std::ostream &a_ostream,
			const BaseMedia &a_media) {
		return a_media.print(a_ostream);
	}

	// Necessary! Needed if a class doens't have one.
	virtual ~BaseMedia() {
	}

	// What class is this? (Rhetorical question).
	virtual int getId() const = 0;
	// Good to have for checking.
	virtual bool operator==(const BaseMedia &) const = 0;
	// Good to have for checking.
	virtual bool operator!=(const BaseMedia &) const = 0;
	// Good to have for sorting.
	virtual bool operator<(const BaseMedia &) const = 0;
};

#endif // BASEMEDIA_H_
