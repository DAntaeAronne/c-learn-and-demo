// Orc.h
#ifndef ORC_H

#define ORC_H

#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Stats.h"

using std::vector;

extern Stats orcStats;

class Orc : public Enemy{
    public:
        Orc() : Enemy(orcStats, CharacterType::orc){}

        vector<Action> lowHealthAction(Character player, vector<Action> playerAction);
        void setDefensiveStance(bool val);

    private:
        bool defensiveStance = false;
};

#endif
