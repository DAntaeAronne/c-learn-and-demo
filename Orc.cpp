// Orc.cpp
#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Orc.h"
#include "Stats.h"
#include "RNG.h"

using std::vector;


// When the Orc reaches the low health threshold
//  Increase defense and lower attack
vector<Action> Orc::lowHealthAction(Character player, vector<Action> playerAction){
    vector<Action> action;
    if (!defensiveStance){
        setDefensiveStance(true);

        Character::setBaseStat(StatType::defense, (getBaseStat(StatType::defense) *2));
        Character::setBaseStat(StatType::attackDmg, (getBaseStat(StatType::attackDmg) / 2));
    }

    return Enemy::enemyChooseAction(player, playerAction);
} // End of lowHealthAction method


void Orc::setDefensiveStance(bool val){
    defensiveStance = val;
}
