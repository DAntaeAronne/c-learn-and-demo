// Combat.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include <limits>
#include <iomanip>
#include "Combat.h"
#include "Character.h"
#include "Enemy.h"
#include "Stats.h"
#include "Equipment.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::max;
using std::streamsize;
using std::numeric_limits;
using std::setw;

bool endGame;

void combatCommence(vector<Character>& fighters){
    endGame = false;

    // Combat loop
    // So long as the player is alive and there are enemies to fight,
    //  Combat will continue

    Character* player = &fighters[0];

    // Combat loop
    while (player->isAlive() && (fighters.size() > 1)){

        int i = 0;
        vector<AttackOrder> attackOrder;

        // Fighter Choice loop
        //Choose an action for each fighter
        for (Character& fighter : fighters){
            vector<Action> fighterAction;
            Character* target = &fighters[0];

            // If: Fighter is the player
            //  Then: Prompt the player to choose an action
            //       and follow through accordingly
            if (i == 0){
                fighterAction = playerChooseAction();

                // If: Attacking
                //  Then: Choose your target
                if (fighterAction[0] == Action::attack){
                    target = &chooseTarget(fighters);
                }

                i++;
            } // End of Player Choice


            // Else: It is an enemy
            else{

                // The low health threshold will be 25% of thier max health
                int fighterMaxHp = fighter.getBaseStat(StatType::maxHealth) + fighter.getEquipStat(StatType::maxHealth);
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


            AttackOrder tempInfo{&fighter, target, fighterAction};

            switch (fighterAction[0]){
                case Action::attack:
                    attackOrder.push_back(tempInfo);
                    break;

                case Action::defend:
                    fighter.setDefending(true);
                    break;
            } // End of fight action resolve

        } // End of Fighters Choice loop

        if(endGame){
            player->setCurHeatlh(-1);
            break;
        }


        // Sort the attack order based on speed
        std::sort(attackOrder.begin(), attackOrder.end(), [](const AttackOrder& a, const AttackOrder& b) {
            // 'a' comes before 'b' if 'a' is faster
            return (a.attacker->getBaseStat(StatType::attackSpeed) + a.attacker->getEquipStat(StatType::attackSpeed)) > (b.attacker->getBaseStat(StatType::attackSpeed) + b.attacker->getEquipStat(StatType::attackSpeed));
        });

        // All Attacks loop
        // Attack in order from fastest to slowest
        // Allowing multiple attacks to go through as well
        for (AttackOrder& attack : attackOrder){
            int dmg;
            // Damage loop
            for(Action& act : attack.actions){
                dmg = attack.attacker->calcAttackDmg();

                string atr;
                switch(attack.attacker->getCharacterType()){
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

                attack.target->takeDmg(dmg);

                cout << "\n\n";
                if(atr == "You" && !attack.attacker->isAlive()){
                    break;
                }
            } // End of Damage loop

            // If: The target is dead then remove
            //  Then: from fighters and the attackOrder, or end the game if it was the player
            if (!attack.target->isAlive()){

                if (!player->isAlive()){
                    cout << "You died taking " << dmg << " dmg\n\n";
                    endGame = true;
                    break;
                }

                attackOrder.erase(remove_if(attackOrder.begin(), attackOrder.end(),
                    [](AttackOrder& dead) {
                        return !dead.target->isAlive() || !dead.attacker->isAlive();
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

            if(endGame){
                player->setCurHeatlh(-1);
                break;
            }
        } // End of All Attacks loop

        // Resetting fighter states at the end of the turn
        for (Character& fighter : fighters){
            fighter.resetTurn();
        }

    } // End of Combat loop;

    if(!endGame){
        rewardSelection(*player);
    }
} // End of combatCommence method


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


        // If: cin fails (non-integer input)
        //  Then: clear error state and ignore the invalid input
        if (cin.fail()) {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input in the buffer
            continue;
        }

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


Character& chooseTarget(vector<Character>& fighters){
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

            cout << i << ".) " << enType << " HP: " << fighters[i].getCurHealth() << "/"  << (fighters[i].getBaseStat(StatType::maxHealth) + fighters[i].getEquipStat(StatType::maxHealth)) << "\n";
        } // End of print loop

        cout << "Choose your target: ";
        cin >> target;

        // If: cin fails (non-integer input)
        //  Then: clear error state and ignore the invalid input
        if (cin.fail()) {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input in the buffer
            continue;
        }

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


void rewardSelection(Character& player){
    Equipment rewardItem = makeRandomEquipment();
    int equipChoice;
    bool valid = false;
    string itemType;

    switch(rewardItem.getType()){
        case EquipmentType::weapon:
            itemType = "Weapon";
            break;
        case EquipmentType::armor:
            itemType = "Armor";
            break;
        case EquipmentType::helmet:
            itemType = "Helmet";
            break;
    }

    Stats itemStats = rewardItem.getStats();
    string curStat;
    string compare;

    // So long as the player's choice is not valid
    //  They will be prompted to choose a target
    while(!valid){
        cout << "Congrats! Looks like they left something behind. Let's compare...\n";
        std::cout << setw(12) << "New " << itemType << "| Comparison | Current " << itemType << " \n";
        std::cout << "---------------------------------------------------------------------\n";
        for (StatType printStat = StatType::maxHealth; printStat != StatType::count; printStat = static_cast<StatType>(static_cast<int>(printStat) +1)){
            switch (printStat){
                case StatType::maxHealth:
                    curStat = "Max HP";
                    break;
                case StatType::attackDmg:
                    curStat = "Damage";
                    break;
                case StatType::attackSpeed:
                    curStat = "Speed";
                    break;
                case StatType::defense:
                    curStat = "Defense";
                    break;
                case StatType::critChance:
                    curStat = "Crit Chance";
                    break;
                case StatType::critDmgMod:
                    curStat = "Crit Dmg Mod";
                    break;
            }

            if (itemStats[printStat] > player.getEquipStat(printStat)){
                compare = ">";
            }
            else if (itemStats[printStat] == player.getEquipStat(printStat)){
                compare = "=";
            }
            else{
                compare = "<";
            }


            cout << curStat << ": " << itemStats[printStat] << " | " << compare << " | " << player.getEquipStat(printStat) << "\n";
        } // End of print loop

        cout << "\n";
        cout << "Equip? (will replace current item)";
        cin >> equipChoice;

        // If: cin fails (non-integer input)
        //  Then: clear error state and ignore the invalid input
        if (cin.fail()) {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input in the buffer
            continue;
        }

        if (equipChoice == 1 || equipChoice == 0){
            valid = true;
        }
        else {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
        }


        if (equipChoice){
            for (StatType statSwitch = StatType::maxHealth; statSwitch != StatType::count; statSwitch = static_cast<StatType>(static_cast<int>(statSwitch) +1)){
                player.setEquipStat(statSwitch, itemStats[statSwitch], rewardItem.getType());
            }

            cout << "New Item Equipped!\n";
        }
        else {
            cout << "Welp *tosses " << itemType << " aside*\n";
        }
    } // End of Valid loop
} // End of rewardSelection method
