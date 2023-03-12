#pragma once

namespace Map 
{
    enum class EMapTile
    {
        Empty = 48,
        Wall = 35,
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