// Combat.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include "Combat.h"
#include "Character.h"
#include "Enemy.h"
#include "Stats.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;

bool endGame;

void combatCommence(vector<Character>& fighters){
    endGame = false;

    // Combat loop
    // So long as the player is alive and there are enemies to fight,
    //  Combat will continue

    Character& player = fighters[0];

    while (player.isAlive() && (fighters.size() > 1) && !endGame){

        int i = 0;
        vector<AttackOrder> attackOrder;

        // Fighter Choice loop
        //Choose an action for each fighter
        for (Character fighter : fighters){
            vector<Action> fighterAction;
            Character target = {{0,0,0,0,0,0}, CharacterType::goblin};

            // If: Fighter is the player
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

                // The low health threshold will be 25% of thier max health
                int fighterMaxHp = fighter.getBaseStat(EnumStats::maxHealth) + fighter.getEquipStat(EnumStats::maxHealth);
                double lowHealthThreshold = 0.25 * fighterMaxHp;

                // If: They are above the low health threshold
                //  Then: They will choose an action as normal
                if (fighter.getCurHealth() > lowHealthThreshold){
                    fighterAction = static_cast<Enemy&>(fighter).enemyChooseAction();
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


            AttackOrder tempInfo{fighter, target, fighterAction};

            switch (fighterAction[0]){
                case Action::attack:
                    attackOrder.push_back(tempInfo);
                    break;

                case Action::defend:
                    fighter.setDefending(true);
                    break;
            } // End of fight action resolve

        } // End of Fighters Choice loop



        // Sort the attack order based on speed
        std::sort(attackOrder.begin(), attackOrder.end(), [](const AttackOrder& a, const AttackOrder& b) {
            // 'a' comes before 'b' if 'a' is faster
            return (a.attacker.getBaseStat(EnumStats::attackSpeed) + a.attacker.getEquipStat(EnumStats::attackSpeed)) > (b.attacker.getBaseStat(EnumStats::attackSpeed) + b.attacker.getEquipStat(EnumStats::attackSpeed));
        });

        // All Attacks loop
        // Attack in order from fastest to slowest
        // Allowing multiple attacks to go through as well
        for (AttackOrder attack : attackOrder){
            for(Action act : attack.actions){
                int dmg = attack.attacker.calcAttackDmg();

                string atr;
                switch(attack.attacker.getCharacterType()){
                    case CharacterType::goblin:
                        atr = "Goblin";
                        break;
                    case CharacterType::orc:
                        atr = "Orc";
                        break;
                    case CharacterType::skeleton:
                        atr = "Skeleton";
                        break;
                    default:
                        atr = "You";
                        break;
                }
                cout << atr << " is attacking: ";

                attack.target.takeDmg(dmg);

                cout << "\n\n";
                if(atr == "You" && !attack.attacker.isAlive()){
                    cout << "You died taking " << dmg << " dmg\n\n";
                }
            }

            // If: The target is dead then remove
            //  Then: from fighters and the attackOrder, or end the game if it was the player
            if (!attack.target.isAlive()){


                if (!player.isAlive()){
                    break;
                }

                attackOrder.erase(remove_if(attackOrder.begin(), attackOrder.end(),
                    [](AttackOrder& dead) {
                        return !dead.target.isAlive() || !dead.attacker.isAlive();
                    }),
                    attackOrder.end()
                ); // end of Erase for attackOrder

                fighters.erase(remove_if(fighters.begin(), fighters.end(),
                    [](Character& dead) {
                        return !dead.isAlive();
                    }),
                    fighters.end()
                ); // end of Erase for fighters
            } // End of Removal

        } // End of All Attacks loop

        // Resetting fighter states at the end of the turn
        for (Character fighter : fighters){
            fighter.resetTurn();
        }
    } /// End of Combat loop
} /// End of combatCommence method


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

    // If: The player chooses to end the game
    //  Then: Set endGame to true
    if (choice == 9){
        cout << "GAME OVER\n\n";
        endGame = true;
    }

    return actionChoice;
} // end of playerChooseAction method


Character chooseTarget(vector<Character>& fighters){

    string enType;
    int target;
    bool valid = false;

    // So long as the player's choice is not valid
    //  They will be prompted to choose a target
    while(!valid){
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

            cout << i << ".) " << enType << " HP: " << fighters[i].getCurHealth() << "/"  << (fighters[i].getBaseStat(EnumStats::maxHealth) + fighters[i].getEquipStat(EnumStats::maxHealth)) << "\n";
        } // End of print loop

        cout << "Choose your target: ";
        cin >> target;

        // If choice is one of the actions then end the loop
        if (((target >= 1) && (target < fighters.size()))){
            valid = true;
        }

        else{
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
        }
    } // End of Valid loop

    return fighters[target];
} // end of chooseTarget method
