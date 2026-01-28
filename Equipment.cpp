// Equipment.cpp

#include <iostream>
#include "Equipment.h"
#include "Stats.h"
#include "RNG.h"


Equipment::Equipment(Stats itemStats, EquipmentType itemType):
    stats(itemStats), type(itemType){
}

Stats Equipment::getStats(){
    return stats;
}


EquipmentType Equipment::getType(){
    return type;
}


// Equipment will have 100 total stat points that will be spread randomly amongst the stats
Equipment makeRandomEquipment(){
    int totalStatsPointsLeft = 100;
    int statPoints;
    Stats itemStats{0,0,0,0,0,0};
    EquipmentType randItemType = static_cast<EquipmentType>(randomNumber() % (static_cast<int>(EquipmentType::count)));
    StatType randStatType;

    // Stat Distribution loop
    while(totalStatsPointsLeft != 0){
        randStatType = static_cast<StatType>(randomNumber() % (static_cast<int>(StatType::count) - 1));
        statPoints = randomNumber() % (totalStatsPointsLeft + 1);
        totalStatsPointsLeft -= statPoints;

        std::cout << "!! STATS: " << statPoints << "\n";

        itemStats[randStatType] = statPoints;
    } // End of Stat Distribution loop

    Equipment itemMade(itemStats, randItemType);

    return itemMade;
} // End of makeRandomEquipment method
