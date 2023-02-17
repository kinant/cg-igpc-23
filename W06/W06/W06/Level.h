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
        vector<char> Map;
        FLevelDimensions Dimensions;
    };

    enum class EMapTile : char {
        Empty = ' ',
        HWall = '-',
        VWall = '|',
        Key = '*',
        Door = 'D',
        Goal = 'X',
        Corner = '+'
    };
}
