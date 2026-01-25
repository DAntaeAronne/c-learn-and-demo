// Goblin.cpp
#include <vector>
#include "Goblin.h"
#include "Character.h"
#include "Stats.h"
#include "RNG.h"

using std::vector;

vector<Action> Goblin::chooseAction(){
    vector<Action> action;
    action.push_back(static_cast<Action>(randomNumber() % static_cast<int>(Action::count)));

    return action;
} // End of chooseAction method

// When the Goblin reaches the low health threshold
//  12.5% for a new goblin to take its place in death
vector<Action> Goblin::lowHealthAction(){
    vector<Action> action;

    return action;
} // End of lowHealthAction method
