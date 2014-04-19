#ifndef _STRING_HELPER_H_
#define _STRING_HELPER_H_

/**
 * Included files
 */
#include <sstream>
#include <string>

namespace StringHelper {
	template <typename T>
	static std::string concat(std::string str1, T str2) {
		std::stringstream result;
		result << str1 << str2;

		return result.str();
	} // concat
};

#endif
