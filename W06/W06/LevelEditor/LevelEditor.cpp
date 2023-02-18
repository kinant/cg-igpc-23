#include <iostream>
#include "raylib.h"

#include "ACursor.h"
#include "../W06/Level.h"

using std::cin;
using std::cout;
using std::endl;

using namespace Level;

void GetLevelDimensions(FLevel& Level);
void RenderLevel(FLevel& Level);
void RenderTopBorder(int width);
void RenderBottomBorder(int width, int height);
void RenderRightBorder(int height);
void RenderLeftBorder(int width, int height);
void RenderCursor(ACursor& Cursor);
void UpdateCursorPosition(ACursor& Cursor, FLevel& Level);
void HandleDrawInput(ACursor& Cursor, FLevel& Level);

constexpr static int MAP_TILE_SIZE = 32;
constexpr static int CURSOR_SIZE = 32;
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
	GetLevelDimensions(Level);

	// Initialize the vector
	// https://www.scaler.com/topics/2d-vector-cpp/
	vector<vector<char>> StartingVector( Level.Dimensions.Height, vector<char>( Level.Dimensions.Width, ' '));

    for (int i = 0; i < Level.Dimensions.Height; i++) 
    {
        for (int j = 0; j < Level.Dimensions.Width; j++) 
        {
            if (i == 0 || i == Level.Dimensions.Height - 1)
            {
                StartingVector[i][j] = '-';
            }
            if (j == 0 || j == Level.Dimensions.Width - 1) 
            {
                StartingVector[i][j] = '-';
            }
        }
    }

    Level.Level = StartingVector;

    ACursor Cursor = { FCoordinates{ 1, 1} };

	const static int screenWidth = (Level.Dimensions.Width + NUM_BORDER_ROWS) * MAP_TILE_SIZE;
	const static int screenHeight = (Level.Dimensions.Height + NUM_BORDER_ROWS) * MAP_TILE_SIZE;

	InitWindow(screenWidth, screenHeight, "LEVEL EDITOR");

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
        EndDrawing();
	}

	CloseWindow();          // Close window and OpenGL context
}

void GetLevelDimensions(FLevel& Level) 
{
	cout << "Input Level Height: ";
	cin >> Level.Dimensions.Height;

	cout << "Input Level Width: ";
	cin >> Level.Dimensions.Width;
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
            case '-':
            case '|':
            case '+':
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

    cout << endl;

    cout << "LEFT BOUND: " << boundsLeft << endl;
    cout << "RIGHT BOUND: " << boundsRight << endl;
    cout << "TOP BOUND: " << boundsTop << endl;
    cout << "BOTTOM BOUND: " << boundsBottom << endl;

    cout << endl;

    cout << "NEW X: " << NewPosition.X * MAP_TILE_SIZE << endl;
    cout << "NEW Y: " << NewPosition.Y * MAP_TILE_SIZE << endl;

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
            Level.Level[Cursor.GetPosition().Y][Cursor.GetPosition().X] = (char)Map::EMapTile::HWall;
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
