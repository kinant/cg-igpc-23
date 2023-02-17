#pragma once
#include<vector>
#include<iostream>
#include "Map.h"

using std::vector;
using std::cout;
using std::endl;
using Map::FCoordinates;

namespace Level 
{
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
        static void DrawLevel(const FLevel& Level);
    };
}
