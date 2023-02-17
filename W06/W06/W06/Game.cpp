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
    FCoordinates NewPosition{ MPlayer->GetPosition() };

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

    //int Index = MLevel.GetIndexFromCoordinates(NewPosition, MLevel.Dimensions.Width);
    char& MapTile = MLevel->Level[NewPosition.Y][NewPosition.X];

    if (MapTile == (char)Map::EMapTile::Empty)
    {
        MPlayer->SetPosition(NewPosition);
    }
    else if (MapTile == (char)Map::EMapTile::Key)
    {
        MPlayer->SetState(EPlayerState::HasKey);
        MapTile = (char)Map::EMapTile::Empty;
        MPlayer->SetPosition(NewPosition);
    }
    else if (MapTile == (char)Map::EMapTile::Door
        && MPlayer->GetState() == EPlayerState::HasKey)
    {
        MapTile = (char)Map::EMapTile::Empty;
        MPlayer->SetState(EPlayerState::NoKey);
        MPlayer->SetPosition(NewPosition);
    }
    else if (MapTile == (char)Map::EMapTile::Goal)
    {
        MapTile = (char)Map::EMapTile::Empty;
        MPlayer->SetState(EPlayerState::Exited);
        MPlayer->SetPosition(NewPosition);
    }
}

void Game::DrawGame()
{
    system("CLS");

    for (int y = 0; y < MLevel->Dimensions.Height; y++) 
    {
        for (int x = 0; x < MLevel->Dimensions.Width; x++) 
        {
            if (x == MPlayer->GetPosition().X && y == MPlayer->GetPosition().Y) 
            {
                cout << MPlayer->PlayerIcon;
                continue;
            }
            cout << MLevel->Level[y][x];
        }
        cout << endl;
    }
}

bool Game::IsGameDone() const
{
    return MPlayer->GetState() == EPlayerState::Exited;
}
