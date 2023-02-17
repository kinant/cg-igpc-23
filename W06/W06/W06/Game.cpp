#include "Game.h"
#include "UserInput.h"

using Input::UserInput;

Game::Game(APlayer* Player, Level::FLevel* Level)
{
	MPlayer = Player;
	MLevel = Level;
}

void Game::UpdatePlayerPosition()
{
    /*FCoordinates NewPosition{ MPlayer.GetPosition() };

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

    int Index = MLevel.GetIndexFromCoordinates(NewPosition, MLevel.Dimensions.Width);
    char& MapTile = MLevel.Map[Index];

    if (MapTile == (char)Level::EMapTile::Empty)
    {
        MPlayer.SetPosition(NewPosition);
    }
    else if (MapTile == (char)Level::EMapTile::Key)
    {
        MPlayer.SetState(EPlayerState::HasKey);
        MapTile = (char)Level::EMapTile::Empty;
        MPlayer.SetPosition(NewPosition);
    }
    else if (MapTile == (char)Level::EMapTile::Door
        && MPlayer.GetState() == EPlayerState::HasKey)
    {
        MapTile = (char)Level::EMapTile::Empty;
        MPlayer.SetState(EPlayerState::NoKey);
        MPlayer.SetPosition(NewPosition);
    }
    else if (MapTile == (char)Level::EMapTile::Goal)
    {
        MapTile = (char)Level::EMapTile::Empty;
        MPlayer.SetState(EPlayerState::Exited);
        MPlayer.SetPosition(NewPosition);
    }

    DrawPlayerPosition();*/
}

void Game::DrawGame()
{
    system("CLS");

    for (int y = 0; y < MLevel->Dimensions.Height; y++) 
    {
        for (int x = 0; x < MLevel->Dimensions.Width; x++) 
        {
            cout << MLevel->Level[y][x];
        }
        cout << endl;
    }
}

void Game::DrawPlayerPosition()
{
    //int index = Level::FLevel::GetIndexFromCoordinates(MPlayer.GetPosition(), MLevel.Dimensions.Width);
    //MLevel.Map[index] = APlayer::PlayerIcon;
}

bool Game::IsGameDone() const
{
    //return MPlayer.GetState() == EPlayerState::Exited;
    return false;
}
