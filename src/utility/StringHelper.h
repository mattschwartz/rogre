#ifndef _STRING_HELPER_H_
#define _STRING_HELPER_H_

/**
 * Included files
 */
#include <sstream>
#include <string>
#include <vector>

namespace StringHelper {
	template <typename T>
	static std::string concat(std::string str1, T str2) {
		std::stringstream result;
		result << str1 << str2;

		return result.str();
	} // concat

    template <typename T>
    static std::string percent(T a) {
        std::stringstream result;
        result << a << "%";

        return result.str();
    } // percent

    static std::string aOrAn(std::string str) {
        if (str[0] == 'a' || str[0] == 'e' || str[0] == 'i' ||
            str[0] == 'o' || str[0] == 'u') {
            return concat<std::string>("an ", str);
        } // if
        return concat<std::string>("a ", str);
    } // aOrAn

    static std::vector<std::string> split(std::string str, char del) {
        std::vector<std::string> result;
        std::string split;

        split = "";
        for (int i = 0, len = str.length(); i < len; i++) {
            if (str[i] == del) {
                result.push_back(split);
                split = "";
            } // if
            else {
                split += str[i];
            } // else
        } // for

        result.push_back(split);

        return result;
    } // split
};

#endif
