#ifndef COMPARE_H
#define COMPARE_H

#include <cstdio>

class Compare {
public:
	// Compares 2 char arrays
	static bool equal(const char *a_a, const char *a_b) {
		size_t length = strlen(a_a);
		if (length != strlen(a_b)) {
			return false;
		}

		for (size_t i = 0; i < length; ++i) {
			if (a_a[i] != a_b[i]) {
				return false;
			}
		}
		return true;
	}
};

#endif // COMPARE_H
