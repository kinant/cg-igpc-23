#include <iostream>
#include <vector>
#include "UserInput.h"
#include "Level.h"
#include "APlayer.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using Input::UserInput;

using namespace Level;

int GetIndexFromCoordinates(const FCoordinates& C, int Width);
void DrawLevel(const FLevel& Level, const APlayer& Player);
void UpdatePlayerPosition(FLevel& Level, APlayer& Player);

int main() 
{
    constexpr FLevelDimensions LevelDimensions{ 25, 15 };

    vector<char> LevelVect = { 
                       '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','*','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-','-','-','-','-','-','-','-','-','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ','X','|',
                       '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+' 
    };

    FLevel Level = { LevelVect, LevelDimensions };

    APlayer Player = { FCoordinates{1,1}, EPlayerState::NoKey };
    
    while(Player.GetState() != EPlayerState::Exited) 
    {
        system("CLS");
        DrawLevel(Level, Player);
        UpdatePlayerPosition(Level, Player);
    }
    system("CLS");
    DrawLevel(Level, Player);
    cout << "YOU COMPLETED THE LEVEL!";
    cout << endl;
}

int GetIndexFromCoordinates(const FCoordinates& C, int Width)
{
    return C.X + C.Y * Width;
}

void DrawLevel(const FLevel& Level, const APlayer& Player)
{
    for (int y = 0; y < Level.Dimensions.Height; y++) 
    {
        for (int x = 0; x < Level.Dimensions.Width; x++) 
        {
            if (Player.GetPosition().X == x && Player.GetPosition().Y == y) {
                cout << APlayer::PlayerIcon;
                continue;
            }
            cout << Level.Map[GetIndexFromCoordinates({x, y}, Level.Dimensions.Width)];
        }
        cout << endl;
    }
}

void UpdatePlayerPosition(FLevel& Level, APlayer& Player)
{
    FCoordinates NewPosition{ Player.GetPosition()};

    switch (UserInput::GetUserInput())
    {
        case Input::EInput::Up:
        {
            NewPosition.Y--;
            break;
        }
        case Input::EInput::Down:
        {
            NewPosition.Y++;
            break;
        }
        case Input::EInput::Left:
        {
            NewPosition.X--;
            break;
        }
        case Input::EInput::Right:
        {
            NewPosition.X++;
            break;
        }

        default:
            break;
    }

    int Index = GetIndexFromCoordinates(NewPosition, Level.Dimensions.Width);
    char& MapTile = Level.Map[Index];

    if (MapTile == (char)EMapTile::Empty)
    {
        Player.SetPosition(NewPosition);
    }
    else if (MapTile == (char)EMapTile::Key ) 
    {
        Player.SetState(EPlayerState::HasKey);
        MapTile = (char)EMapTile::Empty;
        Player.SetPosition(NewPosition);
    }
    else if (MapTile == (char)EMapTile::Door 
        && Player.GetState() == EPlayerState::HasKey) 
    {
        MapTile = (char)EMapTile::Empty;
        Player.SetState(EPlayerState::NoKey);
        Player.SetPosition(NewPosition);
    }
    else if (MapTile == (char)EMapTile::Goal) 
    {
        MapTile = (char)EMapTile::Empty;
        Player.SetState(EPlayerState::Exited);
        Player.SetPosition(NewPosition);
    }
}
