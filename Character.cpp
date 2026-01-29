// Character.cpp
//
// Array of equipement
//  When new equipment is acquired then all of the stats need to be recombined
#include <iostream>
#include <random>
#include "Character.h"
#include "Stats.h"
#include "RNG.h"

using std::cout;
using std::string;

Character::Character(Stats stats, CharacterType charType) :
    baseStats(stats), type(charType), curHealth(baseStats.maxHealth), defending(false), critHit(false){

    for (int item = static_cast<int>(EquipmentType::weapon); item < static_cast<int>(EquipmentType::count); item++){
        for (StatType stat = StatType::maxHealth; stat != StatType::count; stat = static_cast<StatType>(static_cast<int>(stat) + 1)){
            equipmentBonus[item][stat] = 0;
        }; // end of stat loop
    }; // end of item loop

} // End of Character initialization


int Character::getBaseStat(StatType wantedStat) const{
    return baseStats[wantedStat];
} // End of getBaseStat method


int Character::getEquipStat(StatType wantedStat) const{
    int statVal = 0;

    for (int item = static_cast<int>(EquipmentType::weapon); item < static_cast<int>(EquipmentType::count); item++){
        statVal += equipmentBonus[item][wantedStat];
    };

    return statVal;
} // End of getEquipStat method


int Character::getCurHealth() const{
    return curHealth;
} // End of getCurHealth method


CharacterType Character::getCharacterType() const{
    return type;
} // End of getCharacterType method


void Character::setBaseStat(StatType wantedStat, int val){
    baseStats[wantedStat] = val;
} // End of setBaseStat method


void Character::setEquipStat(StatType wantedStat, int val, EquipmentType item){
    equipmentBonus[static_cast<int>(item)][wantedStat] = val;
} // End of setEquipStat method


void Character::setCurHealth(int val){
    curHealth = val;
} // End of setCurHealth method


void Character::setDefending(bool val){
    defending = val;
} // End of setDefending method


bool Character::isAlive(){
    return (curHealth > 0 ? true : false);
} // End of setEquipStat method


void Character::takeDmg(int dmgTaken){
    int totalDmgTaken;

    // If not defending
    //   Then take damage with only passive defense in mind
    if (!defending){
        totalDmgTaken = static_cast<int>(dmgTaken) * (100.00 / (100 + baseStats.defense + getEquipStat(StatType::defense)));
    }

    // Else
    //   Mulltipy total defense stat by 3
    else{
        totalDmgTaken = dmgTaken * (100.00 / (100 + 3 * (baseStats.defense + getEquipStat(StatType::defense))));
    }

    string target;
    string isAre;

    switch(type){
        case CharacterType::goblin:
            target = "Goblin";
            isAre = "is";
            break;
        case CharacterType::orc:
            target = "Orc";
            isAre = "is";
            break;
        case CharacterType::skeleton:
            target = "Skeleton";
            isAre = "is";
            break;
        default:
            target = "You";
            isAre = "are";
            break;
    }

    setCurHealth(curHealth - totalDmgTaken);

    string endingPhrase;

    if (curHealth <= 0){
        endingPhrase += "died x_x";
    }
    else{

        endingPhrase =  isAre + " now at: " + std::to_string(curHealth);
    }


    cout <<  target << " took " << totalDmgTaken << " dmg and " << endingPhrase << "\n";



} // End of takeDmg method


int Character::calcAttackDmg(){
    // Regardless of the number generated,
    //  the character needs to have a critChance above 0 for crits to be available

    int dmgDealt = randomNumber() % (baseStats.attackDmg + getEquipStat(StatType::attackDmg));
    int totalCritChance = baseStats.critChance + getEquipStat(StatType::critChance);
    int critDmgDone = static_cast<int>(static_cast<double>(dmgDealt) * (1.0 + static_cast<double>(baseStats.critDmgMod + getEquipStat(StatType::critDmgMod)) / 100));

    if (((randomNumber() % 100) < totalCritChance) && (totalCritChance > 0)){
        critHit = true;
        cout << "- WOAH!!! NICE CRIT!!! - ";
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
