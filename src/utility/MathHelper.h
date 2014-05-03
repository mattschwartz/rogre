#ifndef _MATH_HELPER_H_
#define _MATH_HELPER_H_

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
};

#endif
