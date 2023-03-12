#pragma once

#include "../W06/Map.h"

using Map::FCoordinates;

class ACursor
{
public:
    ACursor(FCoordinates Pos);
    void SetPosition(FCoordinates Pos);
    FCoordinates GetPosition() const;

    const static char CursorIcon = '@';
private:
    FCoordinates MPosition;
};
