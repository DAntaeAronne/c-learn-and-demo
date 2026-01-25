// Goblin.h
#ifndef GOBLIN_H

#define GOBLIN_H

#include <vector>
#include "Character.h"
#include "Stats.h"

using std::vector;

extern Stats goblinStats;

class Goblin : public Character{
    public:
        Goblin() : Character(goblinStats, CharacterType::goblin){}

        vector<Action> chooseAction();
        vector<Action> lowHealthAction();
};

#endif
