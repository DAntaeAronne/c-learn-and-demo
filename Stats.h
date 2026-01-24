#ifndef STATS_H

#define STATS_H


enum struct EnumStats{
    maxHealth,
    attackDmg,
    defense,
    critChance,
    critDmgMod,
    count,
};

enum struct Equipment{
    weapon,
    armor,
    helmet,
    count,
};

struct Stats {
    int maxHealth;
    int attackDmg;
    int defense;
    int critChance;
    int critDmgMod;


    int& operator[](EnumStats stat) {
        switch (stat) {
            case EnumStats::maxHealth:
                return maxHealth;

            case EnumStats::attackDmg:
                return attackDmg;

            case EnumStats::defense:
                return defense;

            case EnumStats::critChance:
                return critChance;

            case EnumStats::critDmgMod:
                return critDmgMod;

            default:
                throw std::out_of_range("Invalid stat");
        }
    };

    const int& operator[](EnumStats stat) const {
        return const_cast<Stats&>(*this)[stat];
    };
};

#endif
