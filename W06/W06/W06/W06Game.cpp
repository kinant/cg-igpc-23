#include <iostream>
#include <conio.h>

using std::cout;
using std::cin;
using std::endl;

const char kPlayerSymbol = '@';

struct Coordinates 
{
    int x{};
    int y{};
};

struct LevelDimensions {
    int width{};
    int height{};
};

enum class Input : char {
    W ='W',
    w = 'w',
    A = 'A',
    a = 'a',
    S = 'S',
    s = 's',
    D = 'D',
    d = 'd'
};

int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], Coordinates player, LevelDimensions dimensions);
void UpdatePlayerPosition(Coordinates& player);

int main() {

    constexpr LevelDimensions kLevelDimensions{ 25, 15 };

    char levelArray[]{ '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+',
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
                       '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+' };

    Coordinates player{ 1,1 };
    
    while(true) {
        system("CLS");
        DrawLevel(levelArray, player, kLevelDimensions);
        UpdatePlayerPosition(player);
    }
}

int GetIndexFromCoordinates(int x, int y, int width)
{
    return x + y * width;
}

void DrawLevel(char level[], Coordinates player, LevelDimensions dimensions)
{
    for (int y = 0; y < dimensions.height; y++) 
    {
        for (int x = 0; x < dimensions.width; x++) 
        {
            if (player.x == x && player.y == y) {
                cout << kPlayerSymbol;
                continue;
            }
            cout << level[GetIndexFromCoordinates(x, y, dimensions.width)];
        }
        cout << endl;
    }
}

// https://stackoverflow.com/questions/17095639/bind-a-char-to-an-enum-type
void UpdatePlayerPosition(Coordinates& player)
{
    char input = _getch();

    switch (input)
    {
        case (char)Input::w:
        case (char)Input::W:
        {
            player.y--;
            break;
        }
        case (char)Input::s:
        case (char)Input::S:
        {
            player.y++;
            break;
        }
        case (char)Input::a:
        case (char)Input::A:
        {
            player.x--;
            break;
        }
        case (char)Input::d:
        case (char)Input::D:
        {
            player.x++;
            break;
        }

        default:
            break;
    }
}
