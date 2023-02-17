#pragma once
#include "Level.h";

using namespace Level;

enum class EPlayerState : int
{
    NoKey,
    HasKey,
    Exited
};

class APlayer
{
    public:
        APlayer(FCoordinates Pos, EPlayerState State);
        void SetPosition(FCoordinates Pos);
        FCoordinates GetPosition() const;
        void SetState(EPlayerState S);
        EPlayerState GetState() const;

        const static char PlayerIcon = '@';
    private:
        FCoordinates MPosition;
        EPlayerState MState;
};