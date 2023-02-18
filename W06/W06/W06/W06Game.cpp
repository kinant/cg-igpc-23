#include "raylib.h"
#include <iostream>
#include <vector>
#include "UserInput.h"
#include "Level.h"
#include "APlayer.h"
#include "Game.h"
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

using Input::UserInput;

using namespace Level;

int main() 
{
    constexpr FLevelDimensions LevelDimensions{ 25, 15 };

    vector<vector<char>> LevelArray = {
            {'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','*','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-','-','-','-','-','-','-','-','-','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ','X','|'},
            {'+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+'}
    };

    FLevel Level = { LevelArray, LevelDimensions };

    ACursor Player = { FCoordinates{1,1}, EPlayerState::NoKey };

    Game NewGame = Game(&Player, &Level);

    int screenWidth = LevelDimensions.Width * MAP_TILE_SIZE;
    int screenHeight = LevelDimensions.Height * MAP_TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "KEY QUEST - BY KINAN TURMAN");

    SetTargetFPS(15);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !NewGame.IsGameDone())    // Detect window close button or ESC key
    {
        NewGame.UpdatePlayerPosition();
        NewGame.Render();
    }

    CloseWindow();          // Close window and OpenGL context
}
