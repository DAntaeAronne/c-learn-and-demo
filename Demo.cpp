// Demo.cpp
#include <iostream>
#include <ctime>
#include "Character.h"
#include "Combat.h"
#include "Goblin.h"
#include "Orc.h"
#include "Skeleton.h"


using std::cout;
using std::cin;
using std::getline;
using std::string;

int main(){

    Stats baseStats = {150, 250, 6, 0, 900};
    string statsNames[5] = {"maxHealth", "attackDmg", "defense", "critChance", "critDmgMod"};

    Character MC(baseStats);
    for (int i = 0; i < static_cast<int>(EnumStats::count); i++){

        EnumStats statCheck = static_cast<EnumStats>(i);
        cout << statsNames[i] << ": " << MC.getBaseStat(statCheck) << "\n";
    }

    Skeleton jay = Skeleton();

    cout << "\n\n";
    cout << "Are we alive?\n";

    if (MC.isAlive()){
        cout << "yes";
    }
    else {
        cout << "dead as dirt";
        return 0;
    }

    cout << "\n";
    cout << "Seems you have " << MC.getCurHealth() << " hp left..\n";
    cout << "catch *throws knife*\n\n";

    MC.takeDmg(jay.calcAttackDmg());

    cout << "How are you now?\n";
    cout << "Seems you have " << MC.getCurHealth() << " hp left..\n";
    cout << "catch *throws knife*\n\n";


    MC.setDefending(true);
    MC.takeDmg(MC.getCurHealth() + 10);

    cout << "Well, still around?\n";
    if (MC.isAlive()){
        cout << "yes";
    }
    else {
        cout << "dead as dirt";
        return 0;
    }

    cout << "\n";
    cout << "HOW?!?!\n";
    cout << "With " << MC.getCurHealth() << " hp left?!?!\n";
    cout << "Cheater\n";

    cout << "W-Wait!! You can't attack me ba- *pow*\n";


    for (int i = 0; i < 10; i++){
        cout << "(you did " << jay.calcAttackDmg() << " dmg. Nice)\n";
    }


    cout << "\n\n\n\n\n";
    cout << "test: \n";
    cout << "max health: " << MC.getBaseStat(EnumStats::maxHealth) << "\n\n";
    cout << "cur health: " << MC.getCurHealth();

    return 0;
}
