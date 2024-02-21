#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "entity.h"

class Interactive : public Entity
{
    Q_OBJECT
public:
    Interactive();
    ~Interactive();
    inline Interactive *asInteractive() override { return this; }
};

#endif // INTERACTIVE_H

// TODO: Remove because quest enum will be available for all objects to make it easier for QML
//       Also this class is for DEBUG purposes only. Interactive should be all Entities but only some of them will have Quests generated in lambda
