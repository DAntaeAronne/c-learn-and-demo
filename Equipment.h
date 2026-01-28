// Equipment.h
#ifndef EQUIPMENT_H

#define EQUIPMENT_H

#include "Stats.h"


class Equipment{
    public:
        Equipment(Stats itemStats, EquipmentType itemType);

        Stats getStats();
        EquipmentType getType();

    private:
        Stats stats;
        EquipmentType type;
};

Equipment makeRandomEquipment();

#endif
