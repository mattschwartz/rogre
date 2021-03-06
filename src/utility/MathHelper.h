#ifndef _MATH_HELPER_H_
#define _MATH_HELPER_H_
#include <stdlib.h>

namespace MathHelper {
    template <typename Type>
    static Type max(Type a, Type b) {
        return a > b ? a : b;
    }

	template <typename Type>
	static Type min(Type a, Type b) {
		return a < b ? a : b;
	}

    template <typename Type>
    static Type abs(Type a) {
        return a > 0 ? a : -a;
    }

    template <typename Type>
    static Type greaterIsh(Type a, Type b, Type c) {
        return (a - b) > c;
    }

    template <typename Type>
    static Type lesserIsh(Type a, Type b, Type c) {
        return (b - a) > c;
    }

    template <typename Type>
    static Type equalIsh(Type a, Type b, Type c) {
        return abs<Type>(a - b) <= c;
    }

    template <typename Type>
    static Type tRand(Type min, Type max) {
        Type r = (Type)rand() / RAND_MAX;
        return min + r * (max - min);
    }

    template <typename Type>
    struct range {
        Type min;
        Type max;

        range() {
            min = 0;
            max = 0;
        } // constructor

        range<Type>(Type a, Type b) {
            min = a;
            max = b;
        } // constructor

        bool inRange(Type c) {
            if (c >= min && c <= max) {
                return true;
            }
            return false;
        } // inRange
    };
};

#endif
