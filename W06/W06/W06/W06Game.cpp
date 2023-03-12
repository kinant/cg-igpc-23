#include "raylib.h"
#include <iostream>
#include <sstream>
#include <fstream>
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

using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::string;

using Input::UserInput;

using namespace Level;

<<<<<<< HEAD
=======
bool ReadLevelFile(string path, vector<vector<char>>& LevelVector);
vector<char> ParseLine(string line);


>>>>>>> main
int main() 
{
    vector<vector<char>> LevelArray = {};

    ReadLevelFile("../1.level", LevelArray);

    cout << "HEIGHT: " << LevelArray.size() << endl;
    cout << "WIDTH: " << LevelArray[0].size() << endl;

    const FLevelDimensions LevelDimensions{ LevelArray[0].size(), LevelArray.size()};

    FLevel Level = { LevelArray, LevelDimensions };

    APlayer Player = { FCoordinates{1,1}, EPlayerState::NoKey };

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

vector<char> ParseLine(string line) {

    istringstream sline(line);

    char c;

    vector<char> row;

    cout << "PARSING LINE: ";

    while (sline >> c) {

        cout << c;

        row.push_back(c);
    }

    cout << endl;

    return row;
}

bool ReadLevelFile(string path, vector<vector<char>>& LevelVector) {

    // create empty vector
    vector<vector<int>> board = {};

    // create and open file stream
    ifstream my_file;
    my_file.open(path);

    // check that input file stream object has been successfully created
    if (my_file) {

        // proceed to read the lines of the input stream
        string line;
        while (getline(my_file, line)) {
            // 
            // cout << "LINE READ: " << line << endl;
            // parse the line
            vector<char> parsedVector = ParseLine(line);
            // add vector
            LevelVector.push_back(parsedVector);
        }
    }
    else
    {
        return false;
    }

<<<<<<< HEAD
    cout << "YOU BEAT THE LEVEL" << endl;

=======
    return true;
>>>>>>> main
}
