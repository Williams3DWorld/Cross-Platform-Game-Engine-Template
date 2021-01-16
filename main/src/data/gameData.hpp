#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

namespace ast
{
    struct PlayerStats
    {
    };

	struct InventoryData
    {
    };

    struct QuestData
    {
    };

    struct GameData
    {
        PlayerStats     playerStats;
        InventoryData   inventory;
        QuestData       questData;
    };
}

#endif