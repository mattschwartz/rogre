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

    static std::string aOrAn(std::string str) {
        if (str[0] == 'a' || str[0] == 'e' || str[0] == 'i' ||
            str[0] == 'o' || str[0] == 'u') {
            return concat<std::string>("an ", str);
        } // if
        return concat<std::string>("a ", str);
    } // aOrAn
};

#endif
