#include "Game.h"

Game::Game()
	: m_bIsGameOver(false)
{

}
Game::~Game() 
{

}

bool Game::Load() 
{
	return m_Level.Load("Level1.txt", m_Player.GetXPositionPointer(), m_Player.GetYPositionPointer());
}

void Game::Run() 
{
	Draw();

	m_bIsGameOver = Update();

	if (m_bIsGameOver) 
	{
		Draw();
	}
}

bool Game::IsGameOver() 
{
	return m_bIsGameOver;
}

bool Game::Update() 
{
    char Input = (char) _getch();

    int NewPlayerX = m_Player.GetXPosition();
    int NewPlayerY = m_Player.GetYPosition();

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

    if (m_Level.IsSpace(NewPlayerX, NewPlayerY))
    {
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if (m_Level.IsKey(NewPlayerX, NewPlayerY))
    {
        m_Player.PickupKey();
        m_Level.PickupKey(NewPlayerX, NewPlayerY);
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
        //PlayKeyPickupSound();
    }
    else if (m_Level.IsDoor(NewPlayerX, NewPlayerY) && m_Player.HasKey())
    {
        m_Player.UseKey();
        m_Level.OpenDoor(NewPlayerX, NewPlayerY);
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
        //PlayDoorOpenSound();
    }
    else if (m_Level.IsDoor(NewPlayerX, NewPlayerY) && !m_Player.HasKey())
    {
        //PlayDoorClosedSound();
    }
    else if (m_Level.IsGoal(NewPlayerX, NewPlayerY))
    {
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
        return true;
    }

    return false;
}

void Game::Draw() 
{
    system("CLS");

    for (int Y = 0; Y < m_Level.GetHeight(); Y++)
    {
        for (int X = 0; X < m_Level.GetWidth(); X++)
        {
            if (m_Player.GetXPosition() == X && m_Player.GetYPosition() == Y)
            {
                m_Player.Draw();
                continue;
            }

            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

            if (m_Level.IsDoor(X,Y))
            {
                if (m_Player.HasKey())
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

            m_Level.Draw(X, Y);
        }
        cout << endl;
    }
}