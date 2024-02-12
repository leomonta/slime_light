#include "utils.hpp"

bool streq(const char *lhs, const char *rhs) {
	while (*lhs != '\0' && *rhs != '\0') {
		 if (*lhs != *rhs) {
			return false;
		}
		 ++lhs;
		 ++rhs;
	}

	return true;
}

bool strneq(const char *str, const size_t count, const char *nts) {
	
	for(size_t i = 0; i < count && *nts != '\0'; ++i, ++nts) {
		 if (str[i] != *nts) {
			return false;
		}
	}

	return true;
}

const char *strnchr(const char *str, const char chr, const size_t count) {

	for (size_t i = 0; i < count; ++i) {
		if (str[i] == chr) {
			return str + i;
		}

	}

	return nullptr;
}
