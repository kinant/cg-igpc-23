#include <iostream>
#include <conio.h>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

const char kPlayerSymbol = '@';

using ptrMapTile = char*;

struct Coordinates 
{
    int x{};
    int y{};
};

struct LevelDimensions 
{
    int width{};
    int height{};
};

struct Level 
{
    vector<char> map;
    LevelDimensions dimensions;
};

enum class EPlayerState : int 
{
    NoKey,
    HasKey,
    Exited
};

enum class EMapTile : char {
    Empty = ' ',
    HWall = '-',
    VWall = '|',
    Key   = '*',
    Door  = 'D',
    Goal  = 'X',
    Corner = '+'
};

enum class EInput : char 
{
    W ='W',
    w = 'w',
    A = 'A',
    a = 'a',
    S = 'S',
    s = 's',
    D = 'D',
    d = 'd'
};

class Player 
{
    public:
        Player(Coordinates pos, EPlayerState state)
        {
            m_position = pos;
            m_state = state;
        }
        const static char playerIcon = '@';
        void SetPosition(Coordinates pos) { m_position = pos; }
        Coordinates GetPosition() const { return m_position; }
        void SetState(EPlayerState s) { m_state = s; }
        EPlayerState GetState() const { return m_state; }
    private:
        Coordinates m_position;
        EPlayerState m_state;
};

int GetIndexFromCoordinates(const Coordinates& c, int width);
void DrawLevel(const Level& level, const Player& player);
void UpdatePlayerPosition(Level& level, Player& player);

int main() 
{

    constexpr LevelDimensions kLevelDimensions{ 25, 15 };

    vector<char> levelVect = { 
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

    Level level = { levelVect, kLevelDimensions };

    Player player = { Coordinates{1,1}, EPlayerState::NoKey };
    
    while(player.GetState() != EPlayerState::Exited) 
    {
        system("CLS");
        DrawLevel(level, player);
        UpdatePlayerPosition(level, player);
    }
    system("CLS");
    DrawLevel(level, player);
    cout << "YOU COMPLETED THE LEVEL!";
}

int GetIndexFromCoordinates(const Coordinates& c, int width)
{
    return c.x + c.y * width;
}

void DrawLevel(const Level& level, const Player& player)
{
    for (int y = 0; y < level.dimensions.height; y++) 
    {
        for (int x = 0; x < level.dimensions.width; x++) 
        {
            if (player.GetPosition().x == x && player.GetPosition().y == y) {
                cout << Player::playerIcon;
                continue;
            }
            cout << level.map[GetIndexFromCoordinates({x, y}, level.dimensions.width)];
        }
        cout << endl;
        cout << endl;
    }
}

void UpdatePlayerPosition(Level& level, Player& player)
{
    char input = _getch();

    Coordinates newPosition{ player.GetPosition()};

    switch (input)
    {
        case (char)EInput::w:
        case (char)EInput::W:
        {
            newPosition.y--;
            break;
        }
        case (char)EInput::s:
        case (char)EInput::S:
        {
            newPosition.y++;
            break;
        }
        case (char)EInput::a:
        case (char)EInput::A:
        {
            newPosition.x--;
            break;
        }
        case (char)EInput::d:
        case (char)EInput::D:
        {
            newPosition.x++;
            break;
        }

        default:
            break;
    }

    int index = GetIndexFromCoordinates(newPosition, level.dimensions.width);
    ptrMapTile mapTile = &level.map[index];

    if (*mapTile == (char)EMapTile::Empty)
    {
        player.SetPosition(newPosition);
    }
    else if (*mapTile == (char)EMapTile::Key ) 
    {
        player.SetState(EPlayerState::HasKey);
        *mapTile = (char)EMapTile::Empty;
        player.SetPosition(newPosition);
    }
    else if (*mapTile == (char)EMapTile::Door 
        && player.GetState() == EPlayerState::HasKey) 
    {
        *mapTile = (char)EMapTile::Empty;
        player.SetState(EPlayerState::NoKey);
        player.SetPosition(newPosition);
    }
    else if (*mapTile == (char)EMapTile::Goal) {
        *mapTile = (char)EMapTile::Empty;
        player.SetState(EPlayerState::Exited);
        player.SetPosition(newPosition);
    }
}
