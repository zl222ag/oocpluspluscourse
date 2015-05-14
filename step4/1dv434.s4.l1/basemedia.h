/*
 * basemedia.h
 *
 *  Created on: 12 maj 2015
 *      Author: Zlatko Ladan
 */

#ifndef BASEMEDIA_H_
#define BASEMEDIA_H_

class BaseMedia {
	virtual ~BaseMedia();
	virtual void show();
	virtual int getID();
};

#endif // BASEMEDIA_H_
