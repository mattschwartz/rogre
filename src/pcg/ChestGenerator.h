#ifndef _CHEST_GENERATOR_H_
#define _CHEST_GENERATOR_H_

class ChestDoodad;

class ChestGenerator {
private:
    ChestGenerator() {}
    ChestGenerator(ChestGenerator const&);
    void operator=(ChestGenerator const&);

public:
    static ChestGenerator &getInstance() {
        static ChestGenerator instance;
        return instance;
    } // getInstance

    ChestDoodad *generateChest(int level);
};

#endif
