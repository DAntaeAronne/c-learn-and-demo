// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <stdexcept>

class Character{
    public:
        Character(int hp, int dmg, int def, int critC, int critDmg);

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
                      case EnumStats::maxHealth: return maxHealth;
                      case EnumStats::attackDmg: return attackDmg;
                      case EnumStats::defense: return defense;
                      case EnumStats::critChance: return critChance;
                      case EnumStats::critDmgMod: return critDmgMod;
                      default: throw std::out_of_range("Invalid stat");
                }
            };

            const int& operator[](EnumStats stat) const {
                return const_cast<Stats&>(*this)[stat];
            };
        };


        // Accessors
        int getBaseStat(EnumStats wantedStat);
        int getEquipStat(EnumStats wantedStat);
        int getCurHealth();

        // Modifiers
        void setBaseStat(EnumStats wantedStat, int val);
        void setEquipStat(EnumStats wantedStat, int val, Equipment item);
        void setCurHeatlh(int val);
        void setDefending(bool val);

        // Misc
        bool isAlive();
        void takeDmg(double dmgTaken);
        int calcAttackDmg();
        void resetTurn();

    private:
        Stats baseStats;
        Stats equipmentBonus[3];
        int curHealth;
        bool defending;
        bool critHit;


    }; // End of class declaration

#endif
