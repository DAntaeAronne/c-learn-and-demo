// Goblin.h
#ifndef SKELETON_H

#define SKELETON_H

#include "Character.h"
#include "Stats.h"

Stats skeletonStats = {50, 25, 1, 25, 35};

class Skeleton : public Character{
    public:
        Skeleton() : Character(skeletonStats){}

        void attack();
        void defend();

};

#endif
