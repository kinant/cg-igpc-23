#include <iostream>
#include <fstream>
#include <sstream>
#include "raylib.h"

#include "ACursor.h"
#include "../W06/Level.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::string;

using namespace Level;

void GetLevelDimensions(FLevel& Level);
void SetLevelDimensions(FLevel& Level, vector<vector<char>>& v);
void RenderLevel(FLevel& Level);
void RenderTopBorder(int width);
void RenderBottomBorder(int width, int height);
void RenderRightBorder(int height);
void RenderLeftBorder(int width, int height);
void RenderCursor(ACursor& Cursor);
void UpdateCursorPosition(ACursor& Cursor, FLevel& Level);
void HandleDrawInput(ACursor& Cursor, FLevel& Level);
void UpdateSaveButtonState(Vector2& mousePoint, bool& btnAction, int& btnState, Rectangle& sourceRec, float& frameHeight, Texture2D& button, Rectangle& btnBounds, FLevel& Level);
void SaveLevel(FLevel& Level);

vector<char> ParseLine(string line);
bool ReadLevelFile(string path, vector<vector<char>>& LevelVector);

vector<vector<char>> NewLevelVector(int height, int width);

constexpr static int MAP_TILE_SIZE = 32;
constexpr static int CURSOR_SIZE = 32;
constexpr static int SAVE_BUTTON_H = 35;
constexpr static int SAVE_BUTTON_W = 100;
constexpr static int SAVE_BUTTON_M = 5;
constexpr static int SAVE_BUTTON_NUM_FRAMES = 3;

constexpr static int MAP_CURSOR_SIZE = 32;
constexpr static int NUM_BORDER_COLS = 2;
constexpr static int NUM_BORDER_ROWS = 2;

Color CWalls{ 128, 128, 128, 160 };
Color CDoor{ 100, 100, 100, 255 };
Color CKey{ 0, 255, 0, 255 };
Color CGoal{ 0, 0, 255, 255 };

int main() 
{

    FLevel Level;
    vector<vector<char>> StartingVector;

    // ---- MENU
    cout << "LEVEL EDITOR: Please Choose an Option: " << endl;
    cout << "   1) New Level" << endl;
    cout << "   2) Load Level" << endl;
    cout << "Enter your option: ";
    
    int option;
    cin >> option;

    switch (option) {
        case 1: 
        {
            GetLevelDimensions(Level);
            StartingVector = NewLevelVector(Level.Dimensions.Height, Level.Dimensions.Width);
            break;
        }
        case 2:
        {

            string path;
            system("CLS");

            cout << endl;
            cout << "Please input filename: ";
            cin >> path;

            ReadLevelFile(path, StartingVector);
            SetLevelDimensions(Level, StartingVector);
            break;
        }
        default:
            exit(-1);
            break;
    }

    Level.Level = StartingVector;

    ACursor Cursor = { FCoordinates{ 1, 1} };

	const static int screenWidth = (Level.Dimensions.Width + NUM_BORDER_ROWS) * MAP_TILE_SIZE;
	const static int screenHeight = ((Level.Dimensions.Height + NUM_BORDER_ROWS) * MAP_TILE_SIZE) + SAVE_BUTTON_H + (2 * SAVE_BUTTON_M);

	InitWindow(screenWidth, screenHeight, "LEVEL EDITOR");

    //---- SAVE BUTTON
    Texture2D button = LoadTexture("resources/save_button.png");

    float frameHeight = (float)button.height / SAVE_BUTTON_NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };

    Rectangle btnBounds = { screenWidth / 2.0f - button.width / 2.0f, (screenHeight - SAVE_BUTTON_M) - (button.height / SAVE_BUTTON_NUM_FRAMES), (float) button.width, frameHeight };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f };

	SetTargetFPS(10);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

        RenderTopBorder(Level.Dimensions.Width + NUM_BORDER_COLS);
        RenderLevel(Level);
        RenderBottomBorder(Level.Dimensions.Width + NUM_BORDER_COLS, (Level.Dimensions.Height + NUM_BORDER_COLS) * MAP_TILE_SIZE);
        RenderRightBorder(Level.Dimensions.Height + NUM_BORDER_ROWS);
        RenderLeftBorder(((Level.Dimensions.Width + NUM_BORDER_COLS) * MAP_TILE_SIZE) - MAP_TILE_SIZE, (Level.Dimensions.Height) + NUM_BORDER_ROWS);
        RenderCursor(Cursor);
        UpdateCursorPosition(Cursor, Level);
        HandleDrawInput(Cursor, Level);
        UpdateSaveButtonState(mousePoint, btnAction, btnState, sourceRec, frameHeight, button, btnBounds, Level);
        EndDrawing();
	}

    UnloadTexture(button);

	CloseWindow();          // Close window and OpenGL context
}

void GetLevelDimensions(FLevel& Level) 
{
	cout << "Input Level Height: ";
	cin >> Level.Dimensions.Height;

	cout << "Input Level Width: ";
	cin >> Level.Dimensions.Width;
}

void SetLevelDimensions(FLevel& Level, vector<vector<char>>& v)
{
    Level.Dimensions.Height = v.size();
    Level.Dimensions.Width = v[0].size();
}

void RenderLevel(FLevel& Level)
{
    int startX = (NUM_BORDER_COLS / 2);
    int startY = (NUM_BORDER_ROWS / 2);

    for (unsigned int y = 0; y < Level.Level.size(); y++)
    {
        for (unsigned int x = 0; x < Level.Level[y].size(); x++)
        {
            switch (Level.Level[y][x])
            {
            case '#':
            {
                DrawRectangle((x + startX) * MAP_TILE_SIZE, (y + startY) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CWalls);
                break;
            }
            case 'D':
            {
                DrawRectangle((x + startX) * MAP_TILE_SIZE, (y + startY) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CDoor);
                break;
            }
            case 'X':
            {
                DrawRectangle((x + startX) * MAP_TILE_SIZE, (y + startY) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CGoal);
                break;
            }
            case '*':
            {
                DrawRectangle((x + startX) * MAP_TILE_SIZE, (y + startY) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CKey);
                break;
            }
            default:
                break;
            }
            DrawRectangleLines((x + startX) * MAP_TILE_SIZE, (y + startY) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(CWalls, 0.5f));
        }
    }
}

void RenderTopBorder(int width) 
{
    for (int i = 0; i < width; i++) 
    {
        DrawRectangle(i * MAP_TILE_SIZE, 0, MAP_TILE_SIZE, MAP_TILE_SIZE, BLACK);
    }
}

void RenderBottomBorder(int width, int height) 
{
    for (int i = 0; i < width; i++)
    {
        DrawRectangle(i * MAP_TILE_SIZE, (height - MAP_TILE_SIZE), MAP_TILE_SIZE, MAP_TILE_SIZE, BLACK);
    }
}

void RenderRightBorder(int height) 
{
    for (int i = 0; i < height; i++) 
    {
        DrawRectangle(0, i * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, BLACK);
    }
}

void RenderLeftBorder(int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        DrawRectangle(width, i * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, BLACK);
    }
}

void RenderCursor(ACursor& Cursor) 
{
    int startX = (NUM_BORDER_COLS / 2);
    int startY = (NUM_BORDER_ROWS / 2);

    DrawRectangle((Cursor.GetPosition().X + startX) * MAP_TILE_SIZE, (Cursor.GetPosition().Y + startY) * MAP_TILE_SIZE, CURSOR_SIZE, CURSOR_SIZE, YELLOW);


}

void UpdateCursorPosition(ACursor& Cursor, FLevel& Level) 
{
    FCoordinates NewPosition{ Cursor.GetPosition() };

    if (IsKeyDown(KEY_W))
    {
        NewPosition.Y--;
    }
    else if (IsKeyDown(KEY_S))
    {
        NewPosition.Y++;
    }
    else if (IsKeyDown(KEY_A))
    {
        NewPosition.X--;
    }
    else if (IsKeyDown(KEY_D))
    {
        NewPosition.X++;
    }
    
    int boundsLeft = (NUM_BORDER_ROWS / 2) * MAP_TILE_SIZE;
    int boundsRight = ((Level.Dimensions.Width) * MAP_TILE_SIZE) - (1 + NUM_BORDER_COLS / 2) * MAP_TILE_SIZE;
    int boundsTop = (NUM_BORDER_ROWS / 2) * MAP_TILE_SIZE;
    int boundsBottom = ((Level.Dimensions.Height) * MAP_TILE_SIZE) - (1 + NUM_BORDER_ROWS / 2) * MAP_TILE_SIZE;

    if ((NewPosition.X * MAP_TILE_SIZE >= boundsLeft && NewPosition.X * MAP_TILE_SIZE <= boundsRight) 
        && (NewPosition.Y * MAP_TILE_SIZE <= boundsBottom && NewPosition.Y * MAP_TILE_SIZE >= boundsTop)) 
    {
        Cursor.SetPosition(NewPosition);
    }

}

void HandleDrawInput(ACursor& Cursor, FLevel& Level)
{
    char& MapTile = Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X];

    if (IsKeyReleased(KEY_H)) 
    {
        if (MapTile == (char)Map::EMapTile::Empty) 
        {
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::Wall;
        }
    }
    if (IsKeyReleased(KEY_J))
    {
        if (MapTile == (char)Map::EMapTile::Empty)
        {
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::Door;
        }
    }
    if (IsKeyReleased(KEY_K))
    {
        if (MapTile == (char)Map::EMapTile::Empty)
        {
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::Key;
        }
    }
    if (IsKeyReleased(KEY_G))
    {
        if (MapTile == (char)Map::EMapTile::Empty)
        {
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::Goal;
        }
    }
    if (IsKeyReleased(KEY_DELETE))
    {
        if (MapTile != (char)Map::EMapTile::Empty)
        {
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::Empty;
        }
    }
}

void UpdateSaveButtonState(Vector2& mousePoint, bool& btnAction, int& btnState, Rectangle& sourceRec, float& frameHeight, Texture2D& button, Rectangle& btnBounds, FLevel& Level)
{
    // Update
    mousePoint = GetMousePosition();
    btnAction = false;

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;

    if (btnAction)
    {
        // TODO: Any desired action
        SaveLevel(Level);
    }

    // Calculate button frame rectangle to draw depending on button state
    sourceRec.y = btnState * frameHeight;

    Vector2 v = {0, 0};
    v.x = btnBounds.x;
    v.y = btnBounds.y;  

    DrawTextureRec(button, sourceRec, v, WHITE); // Draw button frame
}

void SaveLevel(FLevel& Level)
{
    // create output file stream
    ofstream outfile("1.level");
    
    for (int y = 0; y < Level.Dimensions.Height; y++) 
    {
        for (int x = 0; x < Level.Dimensions.Width; x++) {
            outfile << Level.Level[y][x];
        }
        if (y != Level.Dimensions.Height - 1) {
            outfile << "\n";
        }
    }

    outfile.close();
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

    return true;
}

vector<vector<char>> NewLevelVector(int height, int width)
{

    // Initialize the vector
    // https://www.scaler.com/topics/2d-vector-cpp/
    vector<vector<char>> StartingVector(height, vector<char>(width, '0'));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                StartingVector[i][j] = '#';
            }
            if (j == 0 || j == width - 1)
            {
                StartingVector[i][j] = '#';
            }
        }
    }

    return StartingVector;
}


