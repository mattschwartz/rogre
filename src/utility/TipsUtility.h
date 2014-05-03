#ifndef _TIPS_UTILITY_H_
#define _TIPS_UTILITY_H_

/**
 * Included files
 */
#include "StringHelper.h"
#include <string>
#include <map>

namespace TipsUtility {
    std::map<int, std::string> tips;

    static void init() {
        using namespace StringHelper;
        std::string dyk = "Did you know ";

        tips[0] = concat<std::string>(dyk, "wombats poop cubes?");
        tips[1] = concat<std::string>(dyk, "coconuts kill more people than sharks per year?");
        tips[2] = concat<std::string>(dyk, "a duck's quack doesn't echo?");
        tips[3] = concat<std::string>(dyk, "on average, 12 newborns are given to the wrong parents per day?");
        tips[4] = concat<std::string>(dyk, "the Oscars given out during WWII were made out of wood?");
        tips[5] = concat<std::string>(dyk, "there are no clocks in Las Vegas?");
        tips[6] = concat<std::string>(dyk, "death is caused by an allergic reaction to dying?");
        tips[7] = concat<std::string>(dyk, "some of these tips are completely facetious?");
        srand(time(NULL));
    }

    static std::string getRandomTip() {
        int i = rand() % tips.size();
        return tips[i];
    } // getRandomTip
};

#endif
