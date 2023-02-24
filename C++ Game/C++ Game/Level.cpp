#include "Level.h"

Level::Level()
	: m_pLevelData(nullptr)
	, m_Width(0)
	, m_Height(0)
{
}

Level::~Level()
{
	if (m_pLevelData != nullptr) 
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}
}

bool Level::Load(string LevelName, int* PlayerX, int* PlayerY)
{
    LevelName.insert(0, "../");

    ifstream LevelFile;
    LevelFile.open(LevelName);

    if (!LevelFile)
    {
        cout << "Opening file failed!" << endl;
        return false;
    }
    else
    {
        constexpr int TempSize = 25;
        char Temp[TempSize];

        LevelFile.getline(Temp, TempSize, '\n');
        m_Width = atoi(Temp);

        LevelFile.getline(Temp, TempSize, '\n');
        m_Height = atoi(Temp);

        m_pLevelData = new char[m_Width * m_Height];

        LevelFile.read(m_pLevelData, (long long) m_Width * m_Height);

        bool bAnyWarnings = Convert(PlayerX, PlayerY);

        if (bAnyWarnings)
        {
            cout << "There were some warnings in the level datta, see above." << endl;
            system("PAUSE");
        }

        return true;
    }
}

void Level::Draw(int X, int Y) const
{
    int Index = GetIndexFromCoordinates(X, Y);
    cout << m_pLevelData[Index];
}

bool Level::IsSpace(int X, int Y) const
{
	return m_pLevelData[GetIndexFromCoordinates(X, Y)] == ' ';
}

bool Level::IsDoor(int X, int Y) const
{
    return m_pLevelData[GetIndexFromCoordinates(X, Y)] == DOR;
}

bool Level::IsKey(int X, int Y) const
{
    return m_pLevelData[GetIndexFromCoordinates(X, Y)] == KEY;
}

bool Level::IsGoal(int X, int Y) const
{
    return m_pLevelData[GetIndexFromCoordinates(X, Y)] == GOL;
}

void Level::PickupKey(int X, int Y)
{
    m_pLevelData[GetIndexFromCoordinates(X, Y)] = ' ';
}

void Level::OpenDoor(int X, int Y)
{
    m_pLevelData[GetIndexFromCoordinates(X, Y)] = ' ';
}

bool Level::Convert(int* PlayerX, int* PlayerY)
{
    bool bAnyWarnings = false;

    for (int Y = 0; Y < m_Height; Y++)
    {
        for (int X = 0; X < m_Width; X++) {
            int Index = GetIndexFromCoordinates(X, Y);

            switch (m_pLevelData[Index])
            {
            case '+':
            case '-':
            case '|':
            {
                m_pLevelData[Index] = WAL;
                break;
            }
            case '*':
            {
                m_pLevelData[Index] = KEY;
                break;
            }
            case 'D':
            {
                m_pLevelData[Index] = DOR;
                break;
            }
            case 'X':
            {
                m_pLevelData[Index] = GOL;
                break;
            }
            case '@':
            {
                m_pLevelData[Index] = ' ';
                
                if (PlayerX != nullptr && PlayerY != nullptr) 
                {
                    *PlayerX = X;
                    *PlayerY = Y;
                }
            }
            case ' ':
            {
                break;
            }
            default:
                cout << "Invalid character in level file: " << m_pLevelData[Index] << endl;
                bAnyWarnings = true;
                break;
            }
        }
    }

    return bAnyWarnings;
}

int Level::GetIndexFromCoordinates(int X, int Y) const
{
    return X + Y * m_Width;
}
