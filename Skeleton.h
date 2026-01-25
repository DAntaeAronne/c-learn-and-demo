// Skeleton.h
#ifndef SKELETON_H

#define SKELETON_H

#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Stats.h"

using std::vector;

extern Stats skeletonStats;

class Skeleton : public Enemy{
    public:
        Skeleton() : Enemy(skeletonStats, CharacterType::skeleton){}

        vector<Action> lowHealthAction();
        void setDefenseLowered(bool val);


    private:
        bool defenseLowered = false;
};

#endif
