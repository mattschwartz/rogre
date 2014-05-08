#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

/**
 * Included files
 */
#include <string>
#include <vector>
#include <set>
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
    void updateSaveMetaFile(std::string playerName);

public:
    static FileManager &getInstance() {
        static FileManager instance;
        return instance;
    } // getInstance

    void init();
    std::vector<std::string> getGraveyard();
    void addToGraveyard(Player *player);
    std::set<std::string> getLoadablePlayers();
    Player *loadPlayer(std::string filepath, int *, int *, int*, bool*);
    void savePlayer(int seed, Player *player, Zone *zone, bool blindMode);
    std::fstream *openFile(std::string filepath);
    void closeFile(std::fstream *file);
    std::string readLine(std::fstream *file);
};

#endif
