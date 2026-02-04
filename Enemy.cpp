// Enemy.cpp

#include <iostream>
#include <random>
#include <vector>
#include "Character.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Goblin.h"
#include "Orc.h"
#include "RNG.h"
#include "Equipment.h"

using std::string;
using std::vector;

vector<Action> Enemy::enemyChooseAction(Character player, vector<Action> playerAction){
    vector<Action> action;
    Action chosen;
    int actionRN;
    bool valid = false;

    int playerDef = 100.00 / (100 + player.getBaseStat(StatType::defense) + player.getEquipStat(StatType::defense));
    int playerAtkDmg = player.getBaseStat(StatType::attackDmg) + player.getEquipStat(StatType::attackDmg);
    int enemyAtkDmg = Character::getBaseStat(StatType::attackDmg) + Character::getEquipStat(StatType::attackDmg);


    // If the enemy has the damage to potentially kill the player
    //  Then the enemy is more likely to attack (3/4 chance);
    if((enemyAtkDmg * playerDef) >= player.getCurHealth()){
        actionRN = randomNumber() % 4;

        if (actionRN >= 0 && actionRN <= 2){
            action.push_back(Action::attack);
        }
        else{
            action.push_back(Action::defend);
        }
    }

    // If the player is attaking and has the total damage to possibly kill the enemy
    //  Then the enemy is more likely to defend (2/3 chance);
    else if ((playerAction[0] == Action::attack) && (playerAtkDmg >= Character::getCurHealth())){
        actionRN = randomNumber() % 3;

        if (actionRN == 0 || actionRN == 1){
            action.push_back(Action::defend);
        }
        else{
            action.push_back(Action::attack);
        }
    }

    // If the player is defending
    //  Then always go for an attack
    else if (playerAction[0] == Action::defend){
        action.push_back(Action::attack);
    }

    else{
        chosen = static_cast<Action>(randomNumber() % static_cast<int>(Action::count));

        while (chosen == Action::lowHealth){
            chosen = static_cast<Action>(randomNumber() % static_cast<int>(Action::count));
        }
        action.push_back(chosen);
    }

    string enemy;
    switch(Character::getCharacterType()){
        case CharacterType::goblin:
            enemy = "Goblin";
            break;
        case CharacterType::orc:
            enemy = "Orc";
            break;
        case CharacterType::skeleton:
            enemy = "Skeleton";
            break;
    }

    if (action[0] == Action::defend){
        std :: cout << "\n" << enemy << " is defending!\n\n";
    }

    return action;
} // End of chooseAction method

Enemy makeRandomEnemy(){
    // Goblin as place holder
    Enemy createdEnemy = Goblin();
    CharacterType enemyType = static_cast<CharacterType>(randomNumber() % static_cast<int>(CharacterType::count));

    // So long as the type is the player
    //  It will keep rolling for a new type
    while (enemyType == CharacterType::player){
        enemyType = static_cast<CharacterType>(randomNumber() % static_cast<int>(CharacterType::count));
    }

    // Create an enemy based on the type
    switch(enemyType){
        case CharacterType::goblin:
            createdEnemy = Goblin();
            break;
        case CharacterType::orc:
            createdEnemy = Orc();
            break;
        case CharacterType::skeleton:
            createdEnemy = Skeleton();
            break;
    }

    Equipment enemyItem = makeRandomEquipment();
    Stats itemStats = enemyItem.getStats();

    for (StatType statSwitch = StatType::maxHealth; statSwitch != StatType::count; statSwitch = static_cast<StatType>(static_cast<int>(statSwitch) +1)){
        createdEnemy.setEquipStat(statSwitch, itemStats[statSwitch], enemyItem.getType());
    }

    createdEnemy.setCurHealth(createdEnemy.getCurHealth() + createdEnemy.getEquipStat(StatType::maxHealth));

    return createdEnemy;
} // End of makeRandomEnemy method
