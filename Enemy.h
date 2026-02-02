// Enemy.h

#ifndef ENEMY_H

#define ENEMY_H

#include <vector>
#include "Character.h"
#include "Stats.h"

using std::vector;

class Enemy : public Character{
    public:
        Enemy(Stats stats, CharacterType charType) : Character(stats, charType){}

        vector<Action> enemyChooseAction(Character player, vector<Action> playerAction);
};

Enemy makeRandomEnemy();

#endif
