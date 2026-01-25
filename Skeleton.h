// Skeleton.h
#ifndef SKELETON_H

#define SKELETON_H

#include <vector>
#include "Character.h"
#include "Stats.h"

using std::vector;

extern Stats skeletonStats;

class Skeleton : public Character{
    public:
        Skeleton() : Character(skeletonStats, CharacterType::skeleton){}

        vector<Action> chooseAction();
        vector<Action> lowHealthAction();

        void setDefenseLowered(bool val);


    private:
        bool defenseLowered = false;
};

#endif
