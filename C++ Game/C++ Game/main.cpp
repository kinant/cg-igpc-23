#include <iostream>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::endl;

constexpr char kPlayerSymbol = '@';

constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;

constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

int GetIndexFromCoordinates(const int X, const int Y, const int Width);
void DrawLevel(const char Level[], const int Width, const int Height, const int PlayerX, const int PlayerY, const bool PlayerHasKey);
bool UpdatePlayerPosition(char Level[], const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey);

void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayKeyPickupSound();
void PlayWinSound();

int main() 
{
    constexpr int kWidth = 25;
    constexpr int kHeight = 15;

	char LevelArray[] = {
            WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',KEY,WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,WAL,' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',WAL,
            WAL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',DOR,' ',' ',' ',' ',' ',' ',' ',' ',GOL,WAL,
            WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL,WAL
    };

    int PlayerX = 1;
    int PlayerY = 1;

    bool PlayerHasKey = false;
    bool GameOver = false;

    while (!GameOver) 
    {
        system("CLS");
        DrawLevel(LevelArray, kWidth, kHeight, PlayerX, PlayerY, PlayerHasKey);
        GameOver = UpdatePlayerPosition(LevelArray, kWidth, PlayerX, PlayerY, PlayerHasKey);
    }

    system("CLS");
    DrawLevel(LevelArray, kWidth, kHeight, PlayerX, PlayerY, PlayerHasKey);
    cout << "YOU WON!!!";
    PlayWinSound();

}

int GetIndexFromCoordinates(int X, int Y, int Width)
{
    return X + Y * Width;
}

void DrawLevel(const char Level[], const int Width, const int Height, const int PlayerX, const int PlayerY, const bool PlayerHasKey)
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

            if (Level[Index] == DOR) 
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

bool UpdatePlayerPosition(char Level[], const int Width, int& PlayerX, int& PlayerY, bool& PlayerHasKey)
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
    else if (Level[Index] == KEY) 
    {
        PlayerHasKey = true;
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
        PlayKeyPickupSound();
    }
    else if (Level[Index] == DOR && PlayerHasKey) 
    {
        PlayerHasKey = false;
        Level[Index] = ' ';
        PlayerX = NewPlayerX;
        PlayerY = NewPlayerY;
        PlayDoorOpenSound();
    }
    else if (Level[Index] == DOR && !PlayerHasKey) 
    {
        PlayDoorClosedSound();
    }
    else if (Level[Index] == GOL) 
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
