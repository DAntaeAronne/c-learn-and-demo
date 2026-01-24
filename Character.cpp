// Character.cpp
//
// Array of equipement
//  When new equipment is acquired then all of the stats need to be recombined
#include <iostream>
#include <random>
#include "Character.h"
#include "Stats.h"
#include "RNG.h"

using std::string;

//const Stats& baseStatsView = baseStats;
//const Stats& equipmentBonusView = equipmentBonus;

Character::Character(Stats stats) :
    baseStats(stats), curHealth(baseStats.maxHealth), defending(false), critHit(false){

    for (int item = static_cast<int>(Equipment::weapon); item < static_cast<int>(Equipment::count); item++){
        for (EnumStats stat = EnumStats::maxHealth; stat != EnumStats::count; stat = static_cast<EnumStats>(static_cast<int>(stat) + 1)){
            equipmentBonus[item][stat] = 0;
        }; // end of stat loop
    }; // end of item loop

} // End of Character initialization


int Character::getBaseStat(EnumStats wantedStat) const{
    return baseStats[wantedStat];

    return 0;
} // End of getBaseStat method


int Character::getEquipStat(EnumStats wantedStat) const{
    int statVal = 0;

    for (int item = static_cast<int>(Equipment::weapon); item < static_cast<int>(Equipment::count); item++){
        statVal += equipmentBonus[item][wantedStat];
    };

    return statVal;
} // End of getEquipStat method


int Character::getCurHealth() const{
    return curHealth;
} // End of getCurHealth method


void Character::setBaseStat(EnumStats wantedStat, int val){
    baseStats[wantedStat] = val;
} // End of setBaseStat method


void Character::setEquipStat(EnumStats wantedStat, int val, Equipment item){
    equipmentBonus[static_cast<int>(item)][wantedStat] = val;
} // End of setEquipStat method


void Character::setCurHeatlh(int val){
    curHealth = val;
} // End of setCurHeatlh method


void Character::setDefending(bool val){
    defending = val;
} // End of setDefending method


bool Character::isAlive(){
    return (curHealth > 0 ? true : false);
} // End of setEquipStat method


void Character::takeDmg(double dmgTaken){
    int totalDmgTaken;

    // If not defending
    //   Then take damage with only passive defense in mind
    if (!defending){
        totalDmgTaken = dmgTaken * (100.00 / (100 + baseStats.defense + getEquipStat(EnumStats::defense)));
    }

    // Else
    //   Mulltipy total defense stat by 3
    else{
        totalDmgTaken = dmgTaken * (100.00 / (100 + 3 * (baseStats.defense + getEquipStat(EnumStats::defense))));
    }

    std::cout << "\ntook " << totalDmgTaken << " dmg\n";
    setCurHeatlh(curHealth - totalDmgTaken);
} // End of takeDmg method


int Character::calcAttackDmg(){
    // Regardless of the number generated,
    //  the character needs to have a critChance above 0 for crits to be available

    int dmgDealt = randomNumber() % (baseStats.attackDmg + getEquipStat(EnumStats::attackDmg));
    int totalCritChance = baseStats.critChance + getEquipStat(EnumStats::critChance);
    int critDmgDone = static_cast<int>(static_cast<double>(dmgDealt) * (1.0 + static_cast<double>(baseStats.critDmgMod + getEquipStat(EnumStats::critDmgMod)) / 100));

    if (((randomNumber() % 100) < totalCritChance) && (totalCritChance > 0)){
        critHit = true;
        std::cout << "- WOAH!!! NICE CRIT!!! - ";
    }

    if (critHit){
        dmgDealt = critDmgDone;
    }

    return dmgDealt;
} // End of calcAttackDmg method


void Character::resetTurn(){
    defending = false;
    critHit = false;
} // End of resetTurn method
