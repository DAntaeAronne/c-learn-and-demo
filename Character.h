// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <stdexcept>
#include "Equipment.h"
#include "Stats.h"

class Character{
    public:
        Character(Stats stats, CharacterType charType);

        // Accessors
        int getBaseStat(StatType wantedStat) const;
        int getEquipStat(StatType wantedStat) const;
        int getEquipStat(EquipmentType item, StatType wantedStat) const;
        int getCurHealth() const;
        CharacterType getCharacterType() const;
        bool getCounterAvailable()  const;
        int getCounterCooldown() const;
        bool getIsCountering() const;
        bool getChargeAvailable()  const;
        int getChargeCooldown() const;
        bool getIsCharging() const;


        // Modifiers
        void setBaseStat(StatType wantedStat, int val);
        void setEquipStat(StatType wantedStat, int val, EquipmentType item);
        void setCurHealth(int val);
        void setDefending(bool val);
        void setCounterCooldown (int val);
        void setCounterAvailable (bool val);
        void setIsCountering(bool val);
        void setChargeAvailable (bool val);
        void setChargeCooldown (int val);
        void setIsCharging (bool val);

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
        bool isCountering = false;
        int counterCooldown = 0;
        bool counterAvailable = true;
        bool isCharging = false;
        int chargeCooldown = 0;
        bool chargeAvailable = true;



    }; // End of class declaration

#endif
