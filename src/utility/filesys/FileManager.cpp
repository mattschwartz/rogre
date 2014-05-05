/**
 * Included files
 */
#include "FileManager.h"

void FileManager::init() {
} // init

std::fstream *FileManager::openFile(std::string filepath) {
    std::fstream *result;

    result->open(filepath);

    if (!result->is_open()) {
        return NULL;
    } // if

    return result;
} // openFile

void FileManager::closeFile(std::fstream *file) {
    file->close();
} // closeFile

std::string FileManager::readLine(std::fstream *file) {
    std::string result;

    std::getline(*file, result);

    if (result.length() <= 1) {
        return "#";
    }

    return result;
} // readLine
