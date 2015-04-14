#ifndef COMPARE_H
#define COMPARE_H

#include <cstdio>

class Compare {
public:
	static bool equal(const char *a, const char *b) {
		size_t length = strlen(a);
		if (length != strlen(b)) {
			return false;
		}

		for (size_t i = 0; i < length; ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}
};

#endif // COMPARE_H
