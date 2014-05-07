#ifndef _TIPS_UTILITY_H_
#define _TIPS_UTILITY_H_

/**
 * Included files
 */
#include "filesys/FileManager.h"
#include <string>
#include <vector>

namespace TipsUtility {
    const std::string TIPS_FILE_PATH = "data/tips.txt";
    std::vector<std::string> tips;

    static void init() {
        FileManager &fileManager = FileManager::getInstance();
        std::fstream *file;
        std::string line;

        file = fileManager.openFile(TIPS_FILE_PATH);

        if (file == NULL) {
            return;
        } // if

        while (!file->eof()) {
            line = fileManager.readLine(file);
        
            if (line[0] == '#') {
                continue;
            } // if

            tips.push_back(line);
        } // while

        fileManager.closeFile(file);
        srand(time(NULL));
    }

    static std::string getRandomTip() {
        int ran = rand() % tips.size();
        auto iter = tips.begin();
        std::string result = "Did you know the tips utility failed to load any tips?";

        std::advance(iter, rand() % tips.size());
        if (!iter->empty()) {
            result = iter->c_str();
        } // if

        return result;
    } // getRandomTip
};

#endif
