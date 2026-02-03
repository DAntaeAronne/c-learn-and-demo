// Goblin.cpp
#include <iostream>
#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Stats.h"
#include "RNG.h"
#include "Equipment.h"

using std::vector;
using std::cout;


// When the Goblin reaches the low health threshold
//  12.5% for a new goblin to take join
vector<Action> Goblin::lowHealthAction(vector<Character>& fighters, Character player, vector<Action> playerAction){

    vector<Action> action;
    int backupCall = randomNumber() % 8;


    if (!callAttempted){
        cout << "The Goblin calling for reinforcements...\n";

        if(backupCall == 0){
            cout << "The call as has been heard!\n";

            Goblin newGoblin = Goblin();

            Equipment enemyItem = makeRandomEquipment();
            Stats itemStats = enemyItem.getStats();

            for (StatType statSwitch = StatType::maxHealth; statSwitch != StatType::count; statSwitch = static_cast<StatType>(static_cast<int>(statSwitch) +1)){
                newGoblin.setEquipStat(statSwitch, itemStats[statSwitch], enemyItem.getType());
            }

            newGoblin.setCurHealth(newGoblin.getCurHealth() + newGoblin.getEquipStat(StatType::maxHealth));

            fighters.push_back(newGoblin);
        }

        else{
            cout << "Seems no one heard him\n";
        }

        setCallAttempted(true);
    } // End of Call Attempt

    // Choose action as normal
    else{
        return Enemy::enemyChooseAction(player, playerAction);
    }

    action.push_back(Action::lowHealth);

    return action;
} // End of lowHealthAction method


void Goblin::setCallAttempted(bool val){
    callAttempted = val;
}
