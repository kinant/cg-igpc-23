#pragma once
#include<vector>

using std::vector;

namespace Level 
{
    struct FCoordinates
    {
        int X{};
        int Y{};
    };

    struct FLevelDimensions
    {
        int Width{};
        int Height{};
    };

    struct FLevel
    {
        char* Map;
        FLevelDimensions Dimensions;
        static int GetIndexFromCoordinates(const FCoordinates& C, int Width);
    };

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
}
