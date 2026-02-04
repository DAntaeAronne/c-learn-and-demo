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

    Stats baseStats = {500, 20, 12, 6, 10, 5};
    string statsNames[5] = {"maxHealth", "attackDmg", "defense", "critChance", "critDmgMod"};

    Character MC(baseStats,  CharacterType::player);
    vector<Character> fighters{MC};

    int maxEnemies = 1;
    int enemiesSlain = 0;

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
