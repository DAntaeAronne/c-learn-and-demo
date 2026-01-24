// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <stdexcept>
#include "Stats.h"

class Character{
    public:
        Character(Stats stats);

        // Accessors
        int getBaseStat(EnumStats wantedStat) const;
        int getEquipStat(EnumStats wantedStat) const;
        int getCurHealth() const;

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
