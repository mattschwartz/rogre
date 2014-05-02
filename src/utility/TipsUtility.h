#ifndef _TIPS_UTILITY_H_
#define _TIPS_UTILITY_H_

/**
 * Included files
 */
#include <string>
#include <map>

namespace TipsUtility {
    std::map<int, std::string> tips;

    static void init() {
        tips[0] = "Did you know this application was written almost entirely by Matt?";
        tips[1] = "Did you know this game was designed, written and envisioned entirely by Matt?";
        tips[2] = "Did you know Matt spent 100+ hours working almost enitrely solo on this application?";
        tips[3] = "If you enjoyed this game, thank Matt. He wrote it all.";
        tips[4] = "You though you had to work in teams on this project? Matt is living proof that this isn't true!";
        tips[5] = "Did you know this game was written in C++?";
        srand(time(NULL));
    }

    static std::string getRandomTip() {
        int i = rand() % tips.size();
        return tips[i];
    } // getRandomTip
};

#endif
