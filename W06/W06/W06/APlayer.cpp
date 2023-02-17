#include "APlayer.h"

APlayer::APlayer(FCoordinates Pos, EPlayerState State)
{
    MPosition = Pos;
    MState = State;
}

void APlayer::SetPosition(FCoordinates Pos) 
{ 
    MPosition = Pos; 
}

FCoordinates APlayer::GetPosition() const 
{ 
    return MPosition; 
}

void APlayer::SetState(EPlayerState S) 
{ 
    MState = S; 
}

EPlayerState APlayer::GetState() const 
{ 
    return 
        MState; 
}