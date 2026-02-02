#ifndef STATS_H

#define STATS_H

#include <stdexcept>

enum struct Action{
    attack,
    defend,
    lowHealth,
    count,
};

enum struct CharacterType {
    player,
    goblin,
    orc,
    skeleton,
    count,
};

enum struct StatType{
    maxHealth,
    attackDmg,
    attackSpeed,
    defense,
    critChance,
    critDmgMod,
    count,
};

enum struct EquipmentType{
    weapon,
    armor,
    helmet,
    count,
};

struct Stats {
    int maxHealth;
    int attackDmg;
    int attackSpeed;
    int defense;
    int critChance;
    int critDmgMod;


    int& operator[](StatType stat) {
        switch (stat) {
            case StatType::maxHealth:
                return maxHealth;

            case StatType::attackDmg:
                return attackDmg;

            case StatType::attackSpeed:
                return attackSpeed;

            case StatType::defense:
                return defense;

            case StatType::critChance:
                return critChance;

            case StatType::critDmgMod:
                return critDmgMod;

            default:
                throw std::out_of_range("Invalid stat");
        }
    };

    const int& operator[](StatType stat) const {
        return const_cast<Stats&>(*this)[stat];
    };
};

#endif
