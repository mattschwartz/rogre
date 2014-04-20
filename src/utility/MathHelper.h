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
};

#endif
