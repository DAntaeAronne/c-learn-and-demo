// Skeleton.cpp
#include <vector>
#include "Skeleton.h"
#include "Character.h"
#include "Stats.h"
#include "RNG.h"

using std::vector;

vector<Action> Skeleton::chooseAction(){
    vector<Action> action;
    action.push_back(static_cast<Action>(randomNumber() % static_cast<int>(Action::count)));

    return action;
} // End of chooseAction method


// When the Skeleton reaches the low health threshold
//  Lower defense and attack twice
vector<Action> Skeleton::lowHealthAction(){

    if (!defenseLowered){
        Character::setBaseStat(EnumStats::defense, (getBaseStat(EnumStats::defense) / 2));
        setDefenseLowered(true);
    }

    return {Action::attack, Action::attack};
} // End of lowHealthAction method

void Skeleton::setDefenseLowered(bool val){
    defenseLowered = val;
} // End of setDefenseLowered method
