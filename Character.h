// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <stdexcept>
#include "Stats.h"


class Character{
    public:
        Character(Stats stats, CharacterType charType);

        // Accessors
        int getBaseStat(EnumStats wantedStat) const;
        int getEquipStat(EnumStats wantedStat) const;
        int getCurHealth() const;
        CharacterType getCharacterType() const;

        // Modifiers
        void setBaseStat(EnumStats wantedStat, int val);
        void setEquipStat(EnumStats wantedStat, int val, Equipment item);
        void setCurHeatlh(int val);
        void setDefending(bool val);

        // Misc
        bool isAlive();
        void takeDmg(int dmgTaken);
        int calcAttackDmg();
        void resetTurn();

    private:
        CharacterType type;
        Stats baseStats;
        Stats equipmentBonus[3];
        int curHealth;
        bool defending;
        bool critHit;


    }; // End of class declaration

#endif
