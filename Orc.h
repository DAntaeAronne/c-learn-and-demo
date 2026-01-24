// Goblin.h
#ifndef ORC_H

#define ORC_H

#include "Character.h"
#include "Stats.h"

Stats orcStats = {200, 30, 10, 5, 25};

class Orc : public Character{
    public:
        Orc() : Character(orcStats){}

        void attack();
        void defend();

};

#endif
