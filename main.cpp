// Demo.cpp
#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
#include <iomanip>
#include "Character.h"
#include "Combat.h"
#include "Enemy.h"
#include "RNG.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::max;
using std::streamsize;
using std::numeric_limits;

void printTutorial();

int main(){

    Stats baseStats = {500, 20, 12, 6, 10, 5};
    string statsNames[5] = {"maxHealth", "attackDmg", "defense", "critChance", "critDmgMod"};

    Character MC(baseStats,  CharacterType::player);
    vector<Character> fighters{MC};

    int maxEnemies = 1;
    int enemiesSlain = 0;

    bool valid = false;
    int startTutOption;

    cout << "WELCOME TO THE GAME\n";

    while(!valid){
        cout << "Select an option:\n";
        cout << "1.) Start Game\n";
        cout << "2.) Tutorial\n";
        cout << "Choice: ";
        cin >> startTutOption;

        // If: cin fails (non-integer input)
        //  Then: clear error state and ignore the invalid input
        if (cin.fail()) {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input in the buffer
            continue;
        }

        if (startTutOption == 1 || startTutOption == 2){
            valid = true;
        }
        else {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
        }

        if (startTutOption == 2){
            printTutorial();
        }

    } // End of Valid loop

    while (fighters[0].isAlive()){
        // Create a random amount of random enemies to send to combat
        // Maximum is 3
        int enemyCount = (randomNumber() % maxEnemies) + 1;

        for (int i = 0; i < enemyCount; i++){
            fighters.push_back(makeRandomEnemy());
        }

        combatCommence(fighters, enemiesSlain);

        maxEnemies++;

        if (maxEnemies > 3){
            maxEnemies--;
        }
    } // End of game

    return 0;
}


void printTutorial(){
    int start;
    bool valid = false;

    cout << "Here's a quick rundown on how to play!\n\n";

    cout << "You have 3 options to choose from in a fight:\n";
    cout << "1.) Attack - Do a basic attack ranging from your base damage up to your total damage points\n";
    cout << "2.) Counter - Take half of the damgae from an enemy and return the other half right back at them\n";
    cout << "             (Careful, this has a 1 turn cooldown)\n";
    cout << "3.) Charge - Spend your turn charging for your next attack to do double damage.\n";
    cout << "             This can still crit but does not have a stacking effect\n";
    cout << "             (Careful, this has a 2 turn cooldown)\n";
    cout << "\n";
    cout << "You will also face 3 types of enemies that have different actions when reaching low health:\n";
    cout << "1.) Goblins - These creeps have the most average stats amongst the enemies\n";
    cout << "              When reaching low health, they will try to call for reinforcements from their goblin tribe\n";
    cout << "2.) Skeletons - These boneheads have the lowest health but can output a shocking amount of damage with increased crit chances\n";
    cout << "              When reaching low health, they will release 2 attacks instead of once as final booms for the glass cannon they are\n";
    cout << "3.) Orcs - These fellas are the tankiest and hardest hitting for base damage\n";
    cout << "              When reaching low health, they will switch to a defensive stance, trying to by time for the other allies to take you down\n";
    cout << "\n";
    cout << "After each fight you will heal as well as find equipment (weapon, armor, or helmet) which each come with their own stats\n";
    cout << "Be sure to compare the new and current item before switching as you might ruin your current build\n";
    cout << "\n";
    cout << "Stats:\n";
    cout << "Max HP - The maximum health you have\n";
    cout << "Damage - The amount of damage that is added to your base damage\n";
    cout << "         The damage done will range from your base damage to your combined damage (not including crits and charge attacks)\n";
    cout << "Speed - Affects your  attacking order, giving you a chance to atack before another enemy may get the chance to kill you\n";
    cout << "Defense - Determines the passive damage reduction when calculating damage\n";
    cout << "Crit Chance - How often you will land a critical strike\n";
    cout << "Crit Dmg Mod - Scales how much damage your critical strike does on top of your regular damage\n";
    cout << "\n";
    cout << "Try to survive as long as you can, the more enemies you kill the better! GOOD LUCK!!\n\n";

    while(!valid){
        cout << "Enter 1 to start: ";
        cin >> start;

        // If: cin fails (non-integer input)
        //  Then: clear error state and ignore the invalid input
        if (cin.fail()) {
            cout << "That's not a choice silly :3 c'mon, try again!\n\n";
            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input in the buffer
            continue;
        }

        if (start == 1){
            valid = true;
        }
        else {
            cout << "Take your time, no rush!\n\n";
        }

    } // End of Valid loop

} // End of printTutorial method
