#include <iostream>
#include <conio.h>

using std::cout;
using std::endl;

constexpr char kPlayerSymbol = '@';

int GetIndexFromCoordinates(const int X, const int Y, const int Width);
void DrawLevel(const char Level[], const int Width, const int Height, const int PlayerX, const int PlayerY);
void UpdatePlayerPosition(char Level[], const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey);

int main() 
{
    constexpr int kWidth = 25;
    constexpr int kHeight = 15;

	char LevelArray[] = {
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

    int PlayerX = 1;
    int PlayerY = 1;

    bool PlayerHasKey = false;

    while (true) 
    {
        system("CLS");
        DrawLevel(LevelArray, kWidth, kHeight, PlayerX, PlayerY);
        UpdatePlayerPosition(LevelArray, kWidth, PlayerX, PlayerY, PlayerHasKey);
    }
}

int GetIndexFromCoordinates(int X, int Y, int Width)
{
    return X + Y * Width;
}

void DrawLevel(const char Level[], const int Width, const int Height, const int PlayerX, const int PlayerY)
{
    for (int Y = 0; Y < Height; Y++) 
    {
        for (int X = 0; X < Width; X++) 
        {
            if (PlayerX == X && PlayerY == Y) 
            {
                cout << kPlayerSymbol;
                continue;
            }

            const int Index = GetIndexFromCoordinates(X, Y, Width);
            cout << Level[Index];
        }
        cout << endl;
    }
}

void UpdatePlayerPosition(char Level[], const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey)
{
    char Input = _getch();

    int NewPlayerX = PlayerX;
    int NewPlayerY = PlayerY;

    switch (Input) 
    {
        case 'w':
        case 'W':
        {
            NewPlayerY--;
            break;
        }
        case 's':
        case 'S':
        {
            NewPlayerY++;
            break;
        }
        case 'a':
        case 'A':
        {
            NewPlayerX--;
            break;
        }
        case 'd':
        case 'D':
        {
            NewPlayerX++;
            break;
        }
        default:
            break;
    }

    int Index = GetIndexFromCoordinates(NewPlayerX, NewPlayerY, Width);

    if (Level[Index] == ' ') 
    {
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
    }
    else if (Level[Index] == '*') 
    {
        PlayerHasKey = true;
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
    }
}
