// Demo.cpp
#include <iostream>
#include <ctime>
#include <vector>
#include "Character.h"
#include "Combat.h"
#include "Goblin.h"
#include "Orc.h"
#include "Skeleton.h"


using std::cout;
using std::cin;
using std::string;
using std::vector;

int main(){

    Stats baseStats = {150, 250, 12, 6, 0, 900};
    string statsNames[5] = {"maxHealth", "attackDmg", "defense", "critChance", "critDmgMod"};

    Character MC(baseStats,  CharacterType::player);

    vector<Character> fighters = {MC};

    while (MC.isAlive()){
        combatCommence(fighters);
    }

    cout << "\nHOPE YOU HAD FUN!\n";

    return 0;
}
