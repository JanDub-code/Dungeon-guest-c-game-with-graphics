#ifndef TILECHOICE_H
#define TILECHOICE_H

#include <vector>
#include <QString>

class tileChoice
{
public:
    tileChoice();
    QString getRandomTile();
    QString getCastle();

private:
    std::vector<QString> tileChoices;
    std::vector<int> tileChances;
    std::vector<QString> tileChoicesCASTLE;
    std::vector<int> tileChancesCASTLE;
};



#endif // TILECHOICE_H
