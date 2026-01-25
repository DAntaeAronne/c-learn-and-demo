// Combat.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include "Combat.h"
#include "Character.h"
#include "Stats.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;

void combatCommence(vector<Character>& fighters){

    // Combat loop
    // So long as the player is alive and there are enemies to fight,
    //  Combat will continue

    Character& player = fighters[0];

    while (player.isAlive() && (fighters.size() > 1)){
        int i = 0;
        vector<AttackOrder> attackOrder;

        // Fighter Choice loop
        //Choose an action for each fighter
        for (Character fighter : fighters){
            vector<Action> fighterAction;
            Character& target = fighter;

            // If: Figher is the player
            //  Then: Prompt the player to choose an action
            //       and follow through accordingly
            if (i == 0){
                fighterAction = playerChooseAction();

                // If: Attacking
                //  Then: Choose your target
                if (fighterAction[0] == Action::attack){
                    target = chooseTarget(fighters);
                }

                i++;
            } // End of Player Choice


            // Else: It is an enemy
            else{
                int fighterMaxHp = fighter.getBaseStat(EnumStats::maxHealth) + fighter.getEquipStat(EnumStats::maxHealth);

                // The low health threshold will be 25% of thier max health
                double lowHealthThreshold = 0.25 * fighterMaxHp;

                // If: They are above the low health threshold
                //  Then: They will choose an action as normal
                if (fighter.getCurHealth() > lowHealthThreshold){
                    fighterAction = playerChooseAction();
                }


                // Else: They will do their own individual low health action unique to their enemy types
                else{
                    break;
                }

                // If: Attacking
                //  Then: Set the plaer as the target
                if (fighterAction[0] == Action::attack){
                    target = player;
                }
            } // End of Enemy Action

            AttackOrder temmpInfo{fighter, target, fighterAction};

            switch (fighterAction[0]){
                case Action::attack:
                    attackOrder.push_back(temmpInfo);
                    break;

                case Action::defend:
                    fighter.setDefending(true);
                    break;
            } // End of fight action resolve

            // Sort the attack order based on speed
            std::sort(attackOrder.begin(), attackOrder.end(), [](const Character& a, const Character& b) {

                // 'a' comes before 'b' if 'a' is faster
                return (a.getBaseStat(EnumStats::attackSpeed) + a.getEquipStat(EnumStats::attackSpeed)) > (b.getBaseStat(EnumStats::attackSpeed) + b.getEquipStat(EnumStats::attackSpeed));
            });

            // All Attacks loop
            // Attack in order from fastest to slowest
            // Allowing multiple attacks to go through as well
            for (AttackOrder attack : attackOrder){
                for(Action act : attack.actions){
                    int dmg = attack.attacker.calcAttackDmg();

                    attack.target.takeDmg(dmg);
                }

                // If: The target is dead then remove
                //  Then: from fighters and the attackOrder, or end the game if it was the player
                if (!attack.target.isAlive()){
                    if (!player.isAlive()){
                        break;
                    }

                    attackOrder.erase_if(
                        [](AttackOrder& dead) {
                            return !dead.target.isAlive() || !dead.attacker.isAlive();
                        }
                    ); // end of Erase for attackOrder

                    fighters.erase_if(attack.target);
                } // End of Removal

            } // End of All Attacks loop

        } // End of Fighters Choice loop

        // Resetting fighter states at the end of the turn
        for (Character fighter : fighters){
            fighter.resetTurn();
        }
    } /// End of Combat loop
}



vector<Action> playerChooseAction(){
    int choice;
    vector<Action> actionChoice;
    bool valid = false;

    // So long as the player's choice is not valid
    //  They will be prompted to choose an action
    while(!valid){
        cout << "What will you do?\n";
        cout << "1.) Attack\n";
        cout << "2.) Defend\n";
        cout << "9.) Leave (End Game)\n";
        cout << "Choice: ";
        cin >> choice;

        // If choice is one of the actions then end the loop
        if (((choice >= 1) && (choice < (static_cast<int>(Action::count) + 1))) || choice == 9){
            valid = true;
        }

        else{
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
        }
    } // End of Valid loop

    cout << "\n";

    actionChoice.push_back(static_cast<Action>(choice - 1));

    return actionChoice;
} // end of playerChooseAction method


Character chooseTarget(vector<Character>& fighters){

    string enType;
    int target;

    for (int i = 1; i < fighters.size(); i++){

        switch(fighters[i].getCharacterType()){
            case CharacterType::goblin:
                enType = "Goblin";
                break;
            case CharacterType::orc:
                enType = "Orc";
                break;
            case CharacterType::skeleton:
                enType = "Skeleton";
                break;
        }

        cout << i << ".) " << enType << "\n";
    } // End of print loop

    cout << "Choose your target: ";
    cin >> target;

    return fighters[target];
}
