// Enemy.cpp

/*




#include "Character.h"
#include "Enemy.h"
#include "RNG.h"
#include <iostream>
#include <random>
#include <typeinfo>

using std::string;


Enemy::Enemy(EnemyType type, int hp, int dmg, int def, int critC, int critDmg) : Character(hp, dmg, def, critC, critDmg) {
    this->type = type;
}


Enemy::~Enemy() {
    // Destructor implementation
}


EnemyType Enemy::getRandomType() {
    int type = randomNumber() % static_cast<int>(EnemyType::count);
    return static_cast<EnemyType>(type);
}


EnemyType Enemy::getType() const {
    return type;
}


Enemy Enemy::makeRandomEnemy() {
    EnemyType type = GetRandomType();

    switch(type):
        case EnemyType::goblin:
            return Enemy(type, 100, 20, 3, 10, 25);

        case EnemyType::orc:
            return Enemy(type, 200, 30, 10, 5, 25);

        case EnemyType::skeleton:
            return Enemy(type, 50, 25, 1, 25, 35);

        default:
            throw std::out_of_range("Enemy creation failed");
}



*/
