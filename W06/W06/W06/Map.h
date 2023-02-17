#pragma once

namespace Map 
{
    enum class EMapTile
    {
        Empty = 32,
        HWall = 45,
        VWall = 124,
        Key = 42,
        Door = 68,
        Goal = 88,
        Corner = 43
    };

    struct FCoordinates
    {
        int X{};
        int Y{};
    };
}