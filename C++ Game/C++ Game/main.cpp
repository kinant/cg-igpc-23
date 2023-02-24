#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "Level.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

constexpr char kPlayerSymbol = '@';

constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

int GetIndexFromCoordinates(const int X, const int Y, const int Width);
void DrawLevel(const char* Level, const int Width, const int Height, const int PlayerX, const int PlayerY, const bool PlayerHasKey);
bool UpdatePlayerPosition(char* Level, const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey);

void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayKeyPickupSound();
void PlayWinSound();

char* LoadLevel(string LevelName, int& Width, int& Height);
bool ConvertLevel(char* Level, const int Width, const int Height, int& PlayerX, int& PlayerY);

int main() 
{
    int Width = 0;
    int Height = 0;

    char* LevelArray = LoadLevel("Level1.txt", Width, Height);

    int PlayerX = 1;
    int PlayerY = 1;

    bool bAnyWarnings = ConvertLevel(LevelArray, Width, Height, PlayerX, PlayerY);

    if (bAnyWarnings) 
    {
        cout << "There were some warnings in the level datta, see above." << endl;
        system("PAUSE");
    }

    bool PlayerHasKey = false;
    bool GameOver = false;

    while (!GameOver) 
    {
        system("CLS");
        DrawLevel(LevelArray, Width, Height, PlayerX, PlayerY, PlayerHasKey);
        GameOver = UpdatePlayerPosition(LevelArray, Width, PlayerX, PlayerY, PlayerHasKey);
    }

    system("CLS");
    DrawLevel(LevelArray, Width, Height, PlayerX, PlayerY, PlayerHasKey);
    cout << "YOU WON!!!";
    PlayWinSound();

    delete[] LevelArray;
    LevelArray = nullptr;
}

char* LoadLevel(string LevelName, int& Width, int& Height) 
{
    LevelName.insert(0, "../");

    ifstream LevelFile;
    LevelFile.open(LevelName);

    if (!LevelFile) 
    {
        cout << "Opening file failed!" << endl;
        return nullptr;
    }
    else 
    {
        constexpr int TempSize = 25;
        char Temp[TempSize];

        LevelFile.getline(Temp, TempSize, '\n');
        Width = atoi(Temp);

        LevelFile.getline(Temp, TempSize, '\n');
        Height = atoi(Temp);

        char* LevelData = new char[Width * Height];

        LevelFile.read(LevelData, Width * Height);

        return LevelData;
    }
}

bool ConvertLevel(char* Level, const int Width, const int Height, int& PlayerX, int& PlayerY) 
{
    bool bAnyWarnings = false;

    for (int Y = 0; Y < Height; Y++) 
    {
        for (int X = 0; X < Width; X++) {
            int Index = GetIndexFromCoordinates(X, Y, Width);

            switch (Level[Index]) 
            {
                case '+':
                case '-':
                case '|': 
                {
                    Level[Index] = Level::WAL;
                    break;
                }
                case '*':
                {
                    Level[Index] = Level::KEY;
                    break;
                }
                case 'D':
                {
                    Level[Index] = Level::DOR;
                    break;
                }
                case 'X':
                {
                    Level[Index] = Level::GOL;
                    break;
                }
                case '@':
                {
                    Level[Index] = ' ';
                    PlayerX = X;
                    PlayerY = Y;
                }
                case ' ':
                {
                    break;
                }
                default:
                    cout << "Invalid character in level file: " << Level[Index] << endl;
                    bAnyWarnings = true;
                    break;
            }
        }
    }

        return bAnyWarnings;
}

int GetIndexFromCoordinates(int X, int Y, int Width)
{
    return X + Y * Width;
}

void DrawLevel(const char* Level, const int Width, const int Height, const int PlayerX, const int PlayerY, const bool PlayerHasKey)
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
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

            if (Level[Index] == Level::DOR) 
            {
                if (PlayerHasKey) 
                {
                    SetConsoleTextAttribute(console, kOpenDoorColor);
                }
                else 
                {
                    SetConsoleTextAttribute(console, kClosedDoorColor);
                }
            }
            else 
            {
                SetConsoleTextAttribute(console, kRegularColor);
            }

            cout << Level[Index];
        }
        cout << endl;
    }
}

bool UpdatePlayerPosition(char* Level, const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey)
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
    else if (Level[Index] == Level::KEY) 
    {
        PlayerHasKey = true;
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
        PlayKeyPickupSound();
    }
    else if (Level[Index] == Level::DOR && PlayerHasKey) 
    {
        PlayerHasKey = false;
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
        PlayDoorOpenSound();
    }
    else if (Level[Index] == Level::DOR && !PlayerHasKey) 
    {
        PlayDoorClosedSound();
    }
    else if (Level[Index] == Level::GOL) 
    {
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
        return true;
    }

    return false;
}

void PlayDoorClosedSound() 
{
    Beep(500, 75);
    Beep(500, 75);

}

void PlayDoorOpenSound() 
{
    Beep(1397, 200);
}

void PlayKeyPickupSound() 
{
    Beep(1568, 200);
}

void PlayWinSound() 
{
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1245, 1000);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1175, 1000);
}
