#include "tilechoice.h"
#include <cstdlib>
#include <ctime>

tileChoice::tileChoice() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    tileChoices = {
        "grass_slab1.png","grass.png", "grass_slab.png", "grass_flower.png","grass_flower1.png",
        "bones.png","grass1.png","grass2.png","grass3.png","grass4.png","grass5.png","grass6.png"
        ,"grass7.png","grass8.png","grass9.png","grass10.png","grass11.png","grass12.png","grass13.png"
    };

    tileChances = {
       10,30,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
    };


    tileChancesCASTLE = {
        1,2,1,10,10
    };


    tileChoicesCASTLE={
                         "Castle/castle1.png", "Castle/castle2.png", "Castle/castle3.png", "Castle/castle7.png", "Castle/castle10.png"


    };
}

QString tileChoice::getRandomTile() {
    int totalChances = 0;


    for (int chance : tileChances) {
        totalChances += chance;
    }


    int randomValue = std::rand() % totalChances;


    for (size_t i = 0; i < tileChoices.size(); ++i) {
        if (randomValue < tileChances[i]) {
            return tileChoices[i];
        }
        randomValue -= tileChances[i];
    }


    return tileChoices[0];
}

QString tileChoice::getCastle() {
    int totalChances = 0;


    for (int chance : tileChancesCASTLE) {
        totalChances += chance;
    }


    int randomValue = std::rand() % totalChances;


    for (size_t i = 0; i < tileChoicesCASTLE.size(); ++i) {
        if (randomValue < tileChancesCASTLE[i]) {
            return tileChoicesCASTLE[i];
        }
        randomValue -= tileChancesCASTLE[i];
    }


    return tileChoicesCASTLE[0];
}



