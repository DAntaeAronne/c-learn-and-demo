// Orc.cpp
#include <vector>
#include "Orc.h"
#include "Character.h"
#include "Stats.h"
#include "RNG.h"

using std::vector;

vector<Action> Orc::chooseAction(){
    vector<Action> action;
    action.push_back(static_cast<Action>(randomNumber() % static_cast<int>(Action::count)));

    return action;
} // End of chooseAction method


// When the Orc reaches the low health threshold
//  Increase defense and lower attack
vector<Action> Orc::lowHealthAction(){
    vector<Action> action;

    return action;
} // End of lowHealthAction method
