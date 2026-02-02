// Demo.cpp
#include <iostream>
#include <ctime>
#include <vector>
#include "Character.h"
#include "Combat.h"
#include "Enemy.h"
#include "RNG.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;

int main(){

    Stats baseStats = {500, 20, 12, 6, 0, 900};
    string statsNames[5] = {"maxHealth", "attackDmg", "defense", "critChance", "critDmgMod"};

    Character MC(baseStats,  CharacterType::player);
    vector<Character> fighters{MC};

    while (fighters[0].isAlive()){
        // Create a random amount of random enemies to send to combat
        // Maximum is 3
        int enemyCount = (randomNumber() % 3) + 1;

        for (int i = 0; i < enemyCount; i++){
            fighters.push_back(makeRandomEnemy());
        }

        combatCommence(fighters);
    } // End of game

    cout << "\nHOPE YOU HAD FUN!\n";

    return 0;
}
