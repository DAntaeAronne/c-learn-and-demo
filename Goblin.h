// Goblin.h
#ifndef GOBLIN_H

#define GOBLIN_H

#include "Character.h"
#include "Stats.h"

Stats goblinStats = {100, 20, 3, 10, 25};

class Goblin : public Character{
    public:
        Goblin() : Character(goblinStats){}

        void attack();
        void defend();

};

#endif
