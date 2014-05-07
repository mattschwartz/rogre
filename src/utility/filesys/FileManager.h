#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

/**
 * Included files
 */
#include <iostream>
#include <fstream>
#include <sstream>

class Player;
class Zone;

class FileManager {
private:
    FileManager() {}
    FileManager(FileManager const&);
    void operator=(FileManager const&);
    std::string timestamp();

public:
    static FileManager &getInstance() {
        static FileManager instance;
        return instance;
    } // getInstance

    void init();
    void savePlayer(int seed, Player *player, Zone *zone);
    std::fstream *openFile(std::string filepath);
    void closeFile(std::fstream *file);
    std::string readLine(std::fstream *file);
};

#endif
