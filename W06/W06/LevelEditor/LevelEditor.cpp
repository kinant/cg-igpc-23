#include <iostream>
#include "raylib.h"

#include "../W06/Level.h"
#include "../W06/APlayer.h"

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

constexpr static int MAP_TILE_SIZE = 32;
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

	const static int screenWidth = (Level.Dimensions.Width + NUM_BORDER_ROWS) * MAP_TILE_SIZE;
	const static int screenHeight = (Level.Dimensions.Height + NUM_BORDER_ROWS) * MAP_TILE_SIZE;

	InitWindow(screenWidth, screenHeight, "LEVEL EDITOR");

	SetTargetFPS(15);

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
                DrawRectangle((x + 1) * MAP_TILE_SIZE, (y + 1) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, CWalls);
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
            DrawRectangleLines((x + 1) * MAP_TILE_SIZE, (y + 1) * MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(CWalls, 0.5f));
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