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

using std::string;
using std::vector;

vector<Action> Enemy::enemyChooseAction(){
    vector<Action> action;
    action.push_back(static_cast<Action>(randomNumber() % static_cast<int>(Action::count)));

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

    return createdEnemy;
} // End of makeRandomEnemy method
