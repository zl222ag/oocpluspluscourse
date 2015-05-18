/*
 * basemedia.h
 *
 *  Created on: 12 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef BASEMEDIA_H_
#define BASEMEDIA_H_

class BaseMedia {
public:
	virtual ~BaseMedia() {
	}
	virtual void show() const = 0;
	virtual int getId() const = 0;
};

#endif // BASEMEDIA_H_
