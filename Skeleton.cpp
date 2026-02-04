// Skeleton.cpp
#include <iostream>
#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Stats.h"
#include "RNG.h"

using std::vector;


// When the Skeleton reaches the low health threshold
//  Lower defense and attack twice
vector<Action> Skeleton::lowHealthAction(){
    std::cout << "Looks like the Skeleton is preparing 2 shots in desperation\n";
    if (!defenseLowered){
        Character::setBaseStat(StatType::defense, (getBaseStat(StatType::defense) / 2));
        setDefenseLowered(true);
    }

    return {Action::attack, Action::attack};
} // End of lowHealthAction method

void Skeleton::setDefenseLowered(bool val){
    defenseLowered = val;
} // End of setDefenseLowered method
