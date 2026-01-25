// Orc.h
#ifndef ORC_H

#define ORC_H

#include <vector>
#include "Character.h"
#include "Stats.h"

using std::vector;

extern Stats orcStats;

class Orc : public Character{
    public:
        Orc() : Character(orcStats, CharacterType::orc){}

        vector<Action> chooseAction();
        vector<Action> lowHealthAction();

};

#endif
