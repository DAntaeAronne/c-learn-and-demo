// Combat.h
#ifndef COMBAT_H

#define COMBAT_H

#include <vector>
#include "Character.h"

using std::vector;

struct AttackOrder {
    Character* attacker;
    Character* target;
    vector<Action> actions;
};

void combatCommence(vector<Character>& fighters, int& enemiesSlain);

void displayEnemies(vector<Character>& fighters);

vector<Action> playerChooseAction(Character& player, int& enemiesSlain);

Character& chooseTarget(vector<Character>& fighters);

void rewardAndHeal(Character& player);

void gameOver(int& enemiesSlain);

#endif
