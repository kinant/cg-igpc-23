#include "ACursor.h"

ACursor::ACursor(FCoordinates Pos)
{
    MPosition = Pos;
}

void ACursor::SetPosition(FCoordinates Pos)
{
    MPosition = Pos;
}

FCoordinates ACursor::GetPosition() const
{
    return MPosition;
}