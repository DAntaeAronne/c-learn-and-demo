// Goblin.h
#ifndef GOBLIN_H

#define GOBLIN_H

#include <vector>
#include "Character.h"
#include "Stats.h"
#include "Enemy.h"

using std::vector;

extern Stats goblinStats;

class Goblin : public Enemy{
    public:
        Goblin() : Enemy(goblinStats, CharacterType::goblin){}

        vector<Action> lowHealthAction();
};

#endif
