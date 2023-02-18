#include "Game.h"

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

void Game::Render() 
{
    DrawLevel();
    DrawPlayer();
}

void Game::DrawLevel()
{
    int screenHeight = MLevel->Dimensions.Width * MAP_TILE_SIZE;
    int screenWidth = MLevel->Dimensions.Height * MAP_TILE_SIZE;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (unsigned int y = 0; y < 15; y++)
    {
        for (unsigned int x = 0; x < 25; x++)
        {
            switch (MLevel->Level[y][x])
            {
            case '-':
            case '|':
            case '+':
            {
                DrawRectangle(x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CWalls);
                break;
            }
            case 'D':
            {
                DrawRectangle(x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CDoor);
                break;
            }
            case 'X':
            {
                DrawRectangle(x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CGoal);
                break;
            }
            case '*':
            {
                DrawRectangle(x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CKey);
                break;
            }
            default:
                break;
            }
            DrawRectangleLines(x * MAP_TILE_SIZE, y * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(CWalls, 0.5f));
        }
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}

void Game::DrawPlayer() 
{
    // Draw tiles from id (and tile borders)
    DrawCircle(MPlayer->GetPosition().X * MAP_TILE_SIZE + (MAP_TILE_SIZE / 2), MPlayer->GetPosition().Y * MAP_TILE_SIZE + (MAP_TILE_SIZE / 2), PLAYER_SIZE / 2, RED);
}

bool Game::IsGameDone() const
{
    return MPlayer->GetState() == EPlayerState::Exited;
}
