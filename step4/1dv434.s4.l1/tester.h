/*
 * tester.h
 *
 *  Created on: 22 maj 2015
 *      Author: zlatko
 */

#ifndef TESTER_H_
#define TESTER_H_

class Tester {
	// Runs the tests for the media register class.
	void testRegister();
	// Runs tests for the music album media class.
	void testMusicAlbumMedia();
	// Runs the tests for the media reader class!
	void testMediaReader();

public:
	// Runs all the tests!
	void runTests();
};

#endif // TESTER_H_
